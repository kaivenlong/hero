#!/usr/bin/env python3

from mako.template import Template
import math
import re

def clog2(x):
    return math.ceil(math.log2(x))

n_clusters = 1
hero_template = Template(filename='hero.template_v')
string = hero_template.render(
    board='zcu102', n_clusters=n_clusters,
    aw=64, dw=128, iw=6+clog2(n_clusters+1), uw=4,
    aw_pl2ps=49, iw_pl2ps=6, uw_pl2ps=1,
    aw_ps2pl=40, iw_ps2pl=16, uw_ps2pl=16,
    aw_lite=32, dw_lite=32,
)
string = re.sub(r'\s+$', '', string, flags=re.M)
print(string)
