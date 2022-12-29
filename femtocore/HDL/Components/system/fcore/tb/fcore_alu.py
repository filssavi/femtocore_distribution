from jinja2 import Template
import argparse
import os

parser = argparse.ArgumentParser(description='Generate femtocore ALU')
parser.add_argument('target', metavar='TARGET', type=str, help='Directory where the output will be generated')
parser.add_argument('--reciprocal', action='store_true', help='Is Reciprocal desired')
parser.add_argument('--name', type=str, help='Name of the produced block diagram')
args = parser.parse_args()



instance_vars = {}

reciprocal_present = args.reciprocal
if args.name is not None:
    instance_vars["design_name"] = args.name
else:
    instance_vars["design_name"] = "fp_alu"

if not reciprocal_present:
    instance_vars["axis_registers"] = ["axis_cmp_0","axis_cmp_1","axis_cmp_2"]
else:
    instance_vars["axis_registers"] = []
    for i in range(0,3):
        instance_vars["axis_registers"].append(f"axis_cmp_{i}")
        instance_vars["axis_registers"].append(f"axis_add_{i}")
        instance_vars["axis_registers"].append(f"axis_mul_{i}")
        instance_vars["axis_registers"].append(f"axis_fti_{i}")
        instance_vars["axis_registers"].append(f"axis_itf_{i}")
    instance_vars["axis_registers"].append(f"axis_cmp_3")
    instance_vars["axis_registers"].append(f"axis_cmp_4")
    instance_vars["axis_registers"].append(f"axis_cmp_5")

instance_vars["reciprocal_present"] = reciprocal_present

template_path = str(os.path.dirname(os.path.realpath(__file__))) + '/FPalu_template.tcl.j2'
with open(template_path) as file_:
    template = Template(file_.read())
        
output = template.render(instance_vars)

with open(args.target, 'w') as f:
    f.write(output)