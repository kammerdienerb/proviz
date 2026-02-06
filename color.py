import math

def name_to_angle(name):
    h = hash(name)
    return (h % 1000000) / 1000000.0 * 2 * math.pi

def stack_to_hsv(stack):
    sum_x      = 0.0
    sum_y      = 0.0
    weight     = 0.999
    min_weight = 0.1
    decay      = 0.9
    saturation = 1.0

    for fn in stack:
        angle = name_to_angle(fn)

        x = math.cos(angle)
        y = math.sin(angle)

        sum_x += weight * x
        sum_y += weight * y

#         weight = max(weight ** (1.0 / decay), min_weight)
        weight = max(weight * decay, min_weight)


#     saturation = min(1.0, math.log(len(stack) + 1) / 3.0)

    normalized = math.atan2(sum_y, sum_x)
    hue = (normalized / (2 * math.pi)) % 1.0

    value = 0.8

    return (hue, saturation, value)

def hsv_to_rgb(h, s, v, a):
    if s:
        if h == 1.0:
            h = 0.0

        i = int(h * 6.0)
        f = h * 6.0 - i

        w = v * (1.0 - s)
        q = v * (1.0 - s * f)
        t = v * (1.0 - s * (1.0 - f))

        if i==0: return (v, t, w, a)
        if i==1: return (q, v, w, a)
        if i==2: return (w, v, t, a)
        if i==3: return (w, q, v, a)
        if i==4: return (t, w, v, a)
        if i==5: return (v, w, q, a)

    else:
        return (v, v, v, a)

path = "yed.stacks"
# path = "proviz.log"
# path = "gcc.stacks"

with open(path) as f:
    for line in f.readlines():
        stack = line.split(";")
#         stack = stack[7:]
        hsv = stack_to_hsv(stack)
        rgb = hsv_to_rgb(hsv[0], hsv[1], hsv[2], 1.0)
        print("\033[48;2;{};{};{};m".format(int(255*rgb[0]), int(255*rgb[1]), int(255*rgb[2])), end="")
        print("{}\033[0m".format(line), end="")
