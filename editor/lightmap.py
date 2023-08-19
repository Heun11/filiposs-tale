import math

# 9x9 lightmap 0-10
lm = [
    [0 ,1 ,1 ,1 ,1 ,1 ,0 ],
    [1 ,1 ,3 ,3 ,3 ,1 ,1 ],
    [1 ,3 ,5 ,6 ,5 ,3 ,1 ],
    [1 ,3 ,6 ,8 ,6 ,3 ,1 ],
    [1 ,3 ,5 ,6 ,5 ,3 ,1 ],
    [1 ,1 ,3 ,3 ,3 ,1 ,1 ],
    [0 ,1 ,1 ,1 ,1 ,1 ,0 ]
]

# convert to float array in c
def covnert_to_c_lightmap(lm, w, h):
    lm_c = "{\n"
    for i in range(w):
        lm_c += "\t"
        for j in range(h):
            lm_c += str(float(lm[i][j]/10))+"f, "
        lm_c+="\n"
    lm_c+="};"
    return lm_c

def light_map(width, height):
    light = []
    center = [width // 2, height // 2]

    value = 10 / math.sqrt((width//2) ** 2)
    for y in range(height):
        light.append([])
        for x in range(width):
            if(10 - value*math.sqrt(abs(width // 2 - x)**2 + abs(height // 2 - y)**2)>0):
                light[y].append(10 - value*math.sqrt(abs(width // 2 - x)**2 + abs(height // 2 - y)**2))
            else:
                light[y].append(0)
    return light

w = 19
h = 19
print(covnert_to_c_lightmap(light_map(w, h), w, h))
