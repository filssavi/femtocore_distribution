#%%(axi_stream_combiner_(\d+))%%
#%%%%

from jinja2 import Template
import argparse, os
import math

parser = argparse.ArgumentParser(description='Generate AXI stream multiplexer')
parser.add_argument('target', metavar='TARGET', type=str,
                    help='Directory where the output will be generated')
parser.add_argument('streams', metavar='streams', type=int,
                    help='Number of streams to multiplex')

args = parser.parse_args()


instance_vars = {}
streams = args.streams
instance_vars['streams'] = list(range(1,streams+1))
instance_vars['n_streams'] = streams
instance_vars['address_width'] = math.ceil(math.log2(streams))-1

template_path = str(os.path.dirname(os.path.realpath(__file__))) + '/AxiStreamMuxGenerator.j2'
with open(template_path) as file_:
    template = Template(file_.read())

output = template.render(instance_vars)


with open(args.target, 'w') as f:
    f.write(output)