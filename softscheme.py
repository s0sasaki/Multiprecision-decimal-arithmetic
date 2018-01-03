
############### Lispy: Scheme Interpreter in Python

## (c) Peter Norvig, 2010; See http://norvig.com/lispy.html

################ Symbol、Procedure、Envクラス

from __future__ import division
import builtins
import bigfloat
import matplotlib.pyplot

python_prompt1 = "python > "
python_prompt2 = "........ "
lisp_prompt1   = "scheme > "
lisp_prompt2   = "........ "

import sys
sys.ps1 = python_prompt1
sys.ps2 = python_prompt2

Symbol = str

class Env(dict):
    "環境: ペア{'var':val}のdictで、外部環境(outer)を持つ。"
    def __init__(self, parms=(), args=(), outer=None):
        self.update(zip(parms,args))
        self.outer = outer
    def find(self, var):
        "var が現れる一番内側のEnvを見つける。"
        return self if var in self else self.outer.find(var)

lisp_shell = True
def python():
    global lisp_shell
    lisp_shell = False
    return sys.ps1

def display(x):
    print(x, end="")

def get_firtst_digit(x): 
    return x.get_frac()[0]

def load_to_scheme(x, name):
    global_env[name] = x

def load_to_python(x, name):  # only for interactive mode
    globals()[name] = x

#def copy_to_scheme(pyname, scmname):
#    global_env[scmname] = globals()[pyname]
#def copy_to_python(scmname, pyname):
#    globals()[pyname] = global_env[scmname] 
    
def fetch_scheme(name):
    return global_env[name]

def fetch_python(name):       # only for interactive mode
    return globals()[name]
    

def plot(x):
    a = list(map(str, x))
    b = list(map(float, a))
    matplotlib.pyplot.plot(b)
    matplotlib.pyplot.show()

def hist(x, filename=False):
    a = list(map(str, x))
    b = list(map(float, a))
    matplotlib.pyplot.hist(b)
    matplotlib.pyplot.show()

def add_globals(env):
    "環境にScheme標準の手続きをいくつか追加する"
    import  operator as op
    env.update(
     {'+':op.add, '-':op.sub, '*':op.mul, '/':op.truediv, 'not':op.not_,
      '>':op.gt, '<':op.lt, '>=':op.ge, '<=':op.le, '=':op.eq, 
      'equal?':op.eq, 'eq?':op.is_, 'length':len, 'cons':lambda x,y:[x]+y,
      'car':lambda x:x[0],'cdr':lambda x:x[1:], 'append':op.add,  
      'list':lambda *x:list(x), 'list?': lambda x:isa(x,list), 
      'null?':lambda x:x==[], 'symbol?':lambda x: isa(x, Symbol)})
    env.update(
    {'sqrt'      : bigfloat.sqrt,
     'exp'       : bigfloat.exp,
     'ln'        : bigfloat.ln,
     'python'    : python,
     'print'     : print,
     'display'   : display,
     'digit1'    : get_firtst_digit,
     'float'     : float,
     'int'       : int,
     'abs'       : lambda x: x if x>=0 else -1*x,
     'max'       : max,
     'sort'      : sorted,
     'nth'       : lambda n,x: x[int(n)],
     'rand_seed' : bigfloat.rand_seed,
     'rand'      : bigfloat.rand,
     'load_to_scheme' : load_to_scheme,
     'load_to_python' : load_to_python,
     #'copy_to_scheme' : copy_to_scheme,
     #'copy_to_python' : copy_to_python,
     'fetch_scheme' : fetch_scheme,
     'fetch_python' : fetch_python,
     'plot'      : plot,
     'hist'      : hist  })
    return env

global_env = add_globals(Env())

isa = isinstance

################ eval

def eval(x, env=global_env):
    "環境の中で式を評価する。"
    if isa(x, Symbol):             # 変数参照
        if x[0]=="\"" and x[-1]=="\"":
            return x[1:-1]
        return env.find(x)[x]
    elif not isa(x, list):         # 定数リテラル
        return x                
    elif x[0] == 'quote':          # (quote exp)
        (_, exp) = x
        return exp
    elif x[0] == 'if':             # (if test conseq alt)
        (_, test, conseq, alt) = x
        return eval((conseq if eval(test, env) else alt), env)
    elif x[0] == 'set!':           # (set! var exp)
        (_, var, exp) = x
        env.find(var)[var] = eval(exp, env)
    elif x[0] == 'define':         # (define var exp)
        (_, var, exp) = x
        env[var] = eval(exp, env)
    elif x[0] == 'lambda':         # (lambda (var*) exp)
        (_, vars, exp) = x
        return lambda *args: eval(exp, Env(vars, args, env))
    elif x[0] == 'begin':          # (begin exp*)
        for exp in x[1:]:
            val = eval(exp, env)
        return val
    else:                          # (proc exp*)
        exps = [eval(exp, env) for exp in x]
        proc = exps.pop(0)
        return proc(*exps)

################ parse、read、ユーザ対話

def read(s):
    "文字列からScheme式を読み込む。"
    return read_from(tokenize(s))

parse = read

def tokenize(s):
    "文字列をトークンのリストに変換する。"
    return s.replace('(',' ( ').replace(')',' ) ').split()


def read_from(tokens):
    "トークンの列から式を読み込む。"
    if len(tokens) == 0:
        raise SyntaxError('unexpected EOF')
    token = tokens.pop(0)
    if '(' == token:
        L = []
        if len(tokens) == 0:
            raise SyntaxError('unexpected EOF')
        while tokens[0] != ')':
            L.append(read_from(tokens))
        tokens.pop(0) # pop off ')'
        return L
    elif ')' == token:
        raise SyntaxError('unexpected )')
    else:
        return atom(token)

def atom(token):
    "数は数にし、それ以外のトークンはシンボルにする。"
    try:
        if token[0] in [str(i) for i in range(10)] or (token[0] in ["+","-"] and token[1] in [str(i) for i in range(10)]):
            return bigfloat.Number(token)
    except:
        pass
    return Symbol(token)

def to_string(exp):
    "PythonオブジェクトをLispの読める文字列に戻す。"
    return '('+' '.join(map(to_string, exp))+')' if isa(exp, list) else str(exp)

def repl():
    "read-eval-print-loopのプロンプト"
    global lisp_shell
    lisp_shell = True
    while lisp_shell:
        l = input(lisp_prompt1)
        if l.replace(" ", "")=="":
            continue
        if l[-1] == '\\':
           l = l[:-1] + ' '
           while True:
               newline = input(lisp_prompt2)
               l = l + newline
               if newline.replace(" ","")=="": 
                   break
        try:
            val = eval(parse(l))
            if val is not None: print(to_string(val))
        except Exception as e:
            #if not isinstance(e, SyntaxError):
            print(type(e).__name__, e)

scheme = repl
 
#def renpl_old(filename):
#    with open(filename) as f:
#        src = f.read()
#        src = "(begin "+src.replace("\n"," ").replace("\\"," ")+")"
#        try:
#            eval(parse(src))
#        except Exception as e:
#            print(type(e).__name__, e)
               
def renpl(filename):    # read-eval-not-print-loop
    with open(filename) as f:
        src = f.read()
        while True:
            try:
                src  = src.split("(python)", maxsplit=1)
                src0 = src[0]
            except IndexError:
                break
            try:
                src0 = "(begin "+src0.replace("\n"," ").replace("\\"," ")+")"
                eval(parse(src0))
            except Exception as e:
                print(type(e).__name__, e)
            if len(src) == 2:
                src = src[1]
            else:
                break
            try:
                src  = src.split("scheme()", maxsplit=1)
                src0 = src[0]
            except Exception as e:
                print(type(e).__name__, e)
            globals()["__builtins__"].exec(src0)
            #builtins.exec(src0)
            if len(src) == 2:
                src = src[1]
            else:
                break

def source_python(filename):
    with open(filename) as f:
        src = f.read()
        globals()["__builtins__"].exec(src)

source_scheme = renpl
global_env.update({"source_scheme":source_scheme})
global_env.update({"source_python":source_python})

def import_scheme(modulename):
    import importlib
    importlib.import_module(modulename)
global_env.update({"import_scheme":import_scheme})


if __name__ == "__main__":
    import sys
    argv = sys.argv
    if len(argv)==1:
        repl()
    else:
        for filename in argv[1:]:
            renpl(filename)
    
