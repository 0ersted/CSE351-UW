# Created by Dylan Johnson and Cody Ohlsen
import sys
import subprocess
import re

ff_bad_binop = re.compile(".*Binop: ((" + \
                            ")|(" + re.escape("|") + \
                            ")|(" + re.escape("|=") + \
                            ")|(" + re.escape("&") + \
                            ")|(" + re.escape("&=") + \
                            ")|(" + re.escape("^") + \
                            ")|(" + re.escape("^=") + \
                            ")|(" + re.escape("&&") + \
                            ")|(" + re.escape("||") + \
                            ")|(" + re.escape(">>") + \
                            ")|(" + re.escape("<<") + \
                            ")|(" + re.escape(">>=") +\
                            ")|(" + re.escape("<<=") + \
                            ")|(" + re.escape("==") + \
                            ")|(" + re.escape(">") + \
                            ")|(" + re.escape("<") + \
                            ")|(" + re.escape(">=") + \
                            ")|(" + re.escape("<=") + "))\s*$")

ff_bad_unary = re.compile(".*Unary: ((" + re.escape("!") + \
                            ")|(" + re.escape("~") + 
                            ")|(" + re.escape("-") + "))\s*$")

sf_bad_binop = re.compile(".*Binop: ((" + \
                            ")|(" + re.escape("|") + \
                            ")|(" + re.escape("|=") + \
                            ")|(" + re.escape("&&") + \
                            ")|(" + re.escape("||") + \
                            ")|(" + re.escape(">") + \
                            ")|(" + re.escape("<") + \
                            ")|(" + re.escape(">=") + \
                            ")|(" + re.escape("<=") + "))\s*$")
sf_bad_unary = re.compile(".*Unary: ((" + re.escape("-") + "))\s*$")

af_bad_constant = re.compile(".*Const:.*(25[6-9]|2[6-9][0-9]|[3-9][0-9][0-9]|\d{4,})U?\s*$")

af_bad_indexing = re.compile(".*Array:\s*$")

restrict = {
  'intSize': (ff_bad_binop, ff_bad_unary, af_bad_constant, af_bad_indexing),
  'doubleSize': (ff_bad_binop, ff_bad_unary, af_bad_constant, af_bad_indexing),
  'pointerSize': (ff_bad_binop, ff_bad_unary, af_bad_constant, af_bad_indexing),
  'changeValue':(sf_bad_binop, sf_bad_unary, af_bad_constant, af_bad_indexing),
  'withinSameBlock': (sf_bad_binop, sf_bad_unary, af_bad_constant, af_bad_indexing),
  'withinArray': (sf_bad_binop, sf_bad_unary, af_bad_constant, af_bad_indexing),
}

grading = len(sys.argv) == 2 and sys.argv[1] == '-g'

if grading:
  grades = [int(x) for x in sys.stdin.readline().split('\t')]
else:
  grades = [1,1,1,3,3,3]

try:
  dlc_output = subprocess.check_output(['./dlc', '-ast', './pointer.c'], stderr=subprocess.STDOUT)
except subprocess.CalledProcessError as e:
  dlc_output = e.output

pointer_funcs = dlc_output.split("Proc:\n  Decl: ")

if len(pointer_funcs) != 7:
  print "dlc.py failed to parse functions, check pointer.c manually"
  sys.exit(0)

if "undeclared!" in dlc_output:
  print "dlc.py failed due to out of order declaration, check pointer.c manually"
  sys.exit(0)

seen_bad_ops = {
  'intSize': [],
  'doubleSize': [],
  'pointerSize': [],
  'changeValue': [],
  'withinSameBlock': [],
  'withinArray': [],
}
final_grade = []
skip_next_line = False
seen_given_bad_op = False
for func, grade in zip(pointer_funcs[1:], grades):
  lines = func.split("\n");
  name = lines[0].split(" ")[0];
  for line in func.split("\n"):
    # skip over any constant values that preceed a "Value:"
    # ast node, these are computed constants, not ones that the
    # student has written themselves.
    if skip_next_line:
      skip_next_line = False
      continue
    if "Value:" in line:
      skip_next_line = True

    for i in range(len(restrict[name])):
      res = restrict[name][i].match(line)
      if res:
        bad_op = res.group(0).lstrip(" ")
        # changeValue is given an index element access, only record > 1 of these
        # in this function
        if not seen_given_bad_op and "Array:" in bad_op and "changeValue" in name:
          seen_given_bad_op = True
          continue
        # change array bad ops to convey more information
        if "Array:" in bad_op:
          bad_op = "Array Indexing []"
        # add this bad_op to the list of currently known bad ops and dock any points
        if 'Const' in bad_op and 'Const' in str(seen_bad_ops[name]):
          # if we have seen a bad constant before, don't dock more points
          # but still add it to the list
          seen_bad_ops[name].append(bad_op)
        elif bad_op not in seen_bad_ops[name]:
          if grade:
            grade -= 1
          seen_bad_ops[name].append(bad_op)
 

  final_grade.append(grade) 

output = ""
if grading:
  for grade in final_grade:
    output += str(grade) + "\t"  

output += str([k + ': ' + str(v) for k, v in seen_bad_ops.iteritems() if len(seen_bad_ops[k])])

print output.rstrip("\t")
