# Copyright 2021 Filippo Savi
# Author: Filippo Savi <filssavi@gmail.com>
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import random
import pandas as pd
import numpy as np
import plotly.express as px

def merge(na, nb, inner_iterations):
    sorted = []
    complexity = inner_iterations
    while len(na)>0 or len(nb)>0:
        complexity +=1
        if len(na)==0:
            sorted.extend(nb)
            return sorted, complexity
        if len(nb)==0:
            sorted.extend(na)
            return sorted, complexity
        if na[0]<nb[0]:
            sorted.append(na[0])
            na.pop(0)
        else:
            sorted.append(nb[0])
            nb.pop(0)

    return sorted, complexity
    

def sort_benchmark(n_in, p_size):
    n = [random.randint(0,100) for x in range(1,n_in+1)]
    inner_iterations = 0

    n_buckets = np.array_split(n, round(len(n)/p_size))

    n.sort();

        
    sorted = []

    for i in n_buckets:
        inner_iterations +=1
        i.sort()
        sorted.append(i.tolist())
        

    n_buckets = sorted
    sorted = []

    while len(n_buckets)>1:

        skip_last = len(n_buckets)%2
        for x in range(0,len(n_buckets),2):
            if skip_last and x==len(n_buckets)-1: 
                sorted.append(n_buckets[x]);
                break;
            na = n_buckets[x]
            nb = n_buckets[x+1]
            merged_arr, inner_iterations = merge(na, nb, inner_iterations)
            sorted.append(merged_arr)

        n_buckets = sorted
        sorted = []

    result = n_buckets[0]
    return inner_iterations;





sort_network_sizes = [2,4,6,8,10,12,14,16]

results = []
merge_sort_wc = dict()

n_runs = 100
array_sizes = [25, 50, 100, 1000]
for arr_s in array_sizes:
    raw_data = dict()
    for ns in sort_network_sizes:
        
        raw_data[ns] = list()
        for i in range(0,n_runs):
            raw_data[ns].append(sort_benchmark(arr_s, ns))

    for ns in sort_network_sizes:
        wc = arr_s*np.log2(arr_s)
        achieved = np.mean(raw_data[ns])
        improvement = round((1-achieved/wc)*100,2)
        results.append({"network_size":ns, "array_size":arr_s, "complexity":achieved, "wc":wc, "improvement":improvement})


df = pd.DataFrame(results)

fig = px.line(df, x="network_size", y="improvement", color='array_size')
fig.show()