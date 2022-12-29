#%%(enable_generator_(\d+))%%
#%%%%
from jinja2 import Template
import argparse, os, subprocess

parser = argparse.ArgumentParser(description='Generate RTCU Multichannel module')
parser.add_argument('target', metavar='TARGET', type=str,
                    help='Directory where the output will be generated')
parser.add_argument('n_enables', metavar='N_ENABLES', type=int,
                    help='Number of enable signals')
parser.add_argument('--A', metavar='ADDR', type=str,
                    help='AXI lite Base address')
args = parser.parse_args()

n_enables = args.n_enables

instance_vars = {}
instance_vars['n_enables'] = n_enables
instance_vars['sb_address'] = ["32'h43bfff0", "32'h43c00000", "32'h43c00100", "32'h43c00200", "32'h43c00300"]

template_path = str(os.path.dirname(os.path.realpath(__file__))) + '/Enable_Generator.j2'
with open(template_path) as file_:
    template = Template(file_.read())

hexify = lambda x : str.replace(hex(x), '0x', '')

template.globals['hexify'] = hexify

output = template.render(instance_vars)


with open(args.target, 'w') as f:
    f.write(output)