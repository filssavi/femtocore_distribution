#%%(axi_stream_combiner_(\d+))%%
#%%%%

from jinja2 import Template
import argparse, os

parser = argparse.ArgumentParser(description='Generate axi stream combiner')
parser.add_argument('target', metavar='TARGET', type=str,
                    help='Directory where the output will be generated')
parser.add_argument('streams', metavar='streams', type=int,
                    help='Number of streams to combine')

args = parser.parse_args()


instance_vars = {}
streams = args.streams
instance_vars['streams'] = list(range(1,streams+1))
instance_vars['n_streams'] = streams


template_path = str(os.path.dirname(os.path.realpath(__file__))) + '/AxiStreamCombinerGenerator.j2'
with open(template_path) as file_:
    template = Template(file_.read())

output = template.render(instance_vars)


with open(args.target, 'w') as f:
    f.write(output)