from __future__ import print_function
import pygame
from flask import Flask, request

import os,sys
 
path = '.\Sounds'
 
if len(sys.argv) == 2:
    path = sys.argv[1]
 
 
files = os.listdir(path)
Sounds = []
for name in files:
    Sounds.append(""".\Sounds\\""" + name)

print(sorted(Sounds))

app = Flask(__name__)


@app.route("/")
def play():
    key = int(request.args.get('key'))
    print('Playing key {}'.format(key))
    pygame.mixer.init(44100, -16,2,2048)
    effect = pygame.mixer.Sound(Sounds[key])
    effect.play()
    return'Playing key {}'.format(key)

# start the server at the port 5000
app.run(host = "0.0.0.0")
