import os
import sys
import random

from config import Config


MAX_INT = 10000
MIN_INT = -MAX_INT


def generate_input(cfg, fb):
    """
    1: find
    2: insert
    3: delete
    4: delete min
    5: delete max
    6: output
    """
    op_num = cfg.op_num
    line = '%d %d\n' % (op_num, cfg.init_size)
    fb.write(line)
    op_num -= 1

    if cfg.allow_duplicate:
        skiplist = [random.randint(MIN_INT, MAX_INT) for i in range(cfg.init_size)]
    else:
        skiplist = random.sample(range(cfg.init_size + 10000), cfg.init_size)
    line = " ".join([str(e) for e in skiplist]) + "\n"
    fb.write(line)

    for _ in range(op_num):
        op = random.choice(cfg.op)
        # insure not find or delete element in an empty list
        if op in [1, 3, 4, 5] and not skiplist:
            op = 2
        if op == 1:
            num = random.randint(MIN_INT, MAX_INT)
            if random.random() < 0.5:
                num = random.choice(skiplist)
            line = "%d %d\n" % (op, num)
            fb.write(line)
        if op == 2:
            num = random.randint(MIN_INT, MAX_INT)
            if not cfg.allow_duplicate:
                while num in skiplist:
                    num = random.randint(MIN_INT, MAX_INT)
            line = "%d %d\n" % (op, num)
            fb.write(line)
            skiplist.append(num)
        if op == 3:
            num = random.choice(skiplist)
            line = "%d %d\n" % (op, num)
            fb.write(line)
            skiplist.remove(num)
        if op == 4:
            line = "%d\n" % op
            fb.write(line)
            num = float('inf')
            for e in skiplist:
                if e < num:
                    num = e
            skiplist.remove(num)
        if op == 5:
            line = "%d\n" % op
            fb.write(line)
            num = -float('inf')
            for e in skiplist:
                if e > num:
                    num = e
            skiplist.remove(num)
        if op == 6:
            line = "%d\n" % op
            fb.write(line)


def main():
    cfg = Config.fromfile('skiplist.py')
    random.seed(cfg.SEED)
    
    if not os.path.isdir(cfg.save_path):
        os.mkdir(cfg.save_path)
        os.mkdir(cfg.save_path + '/input')
        os.mkdir(cfg.save_path + '/output')

    for i in range(cfg.NUM_CASES):
        path = '%s/input/input_%d.txt' % (cfg.save_path, i)
        with open(path, 'w') as fb:
            generate_input(cfg.TEST_CASES[i], fb)


if __name__ == '__main__':
    main()

