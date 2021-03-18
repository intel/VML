#!/usr/bin/python3
import os
import subprocess
from decimal import Decimal
import argparse
import statistics

def run_cmd(cmd, env=None):
    current_env = os.environ.copy()
    if env is not None:
        current_env.update(env)
    try:
        out = subprocess.check_output(cmd, shell=True, env=current_env)
        #print(cmd)
        ll = out.decode('utf-8').split('\n')
        #print(ll)
        ll_2 = ll[2].split('\t')[2].split(' ')[0]
        #print(ll_2)
        return Decimal(ll_2)
    except subprocess.CalledProcessError as e:
        print('output(error): %s' % e.output)
        return e.output

def main():
    parser = argparse.ArgumentParser(description='benchmark data collection tool')
    parser.add_argument('--func', type=str,
                        metavar="func",
                        help='function names such as sin, sinf, cos, cosf...')
    parser.add_argument('--name', type=str,
                        metavar="name",
                        help='test binary name (vector, scalar, scalar_vec)')
    parser.add_argument('--loop', type=int,
                        metavar="loop",
                        help='run times')
    #parser.add_argument('--in_turn', action='store_true', default=False,
    #                    dest='in_turn',
    #                    help='Find the regression on by one')
    args = parser.parse_args()
    
    print(args.func, args.name, args.loop)
    if args.name == "vector":
        test_name = "{}_vector.bin".format(args.func)
    elif args.name == "scalar":
        test_name = "{}_scalar.bin".format(args.func)
    elif args.name == "scalar_vec":
        test_name = "{}_scalar_vec.bin".format(args.func)
    else:
        parser.print_help()
        exit(1)
    print(test_name)
    #numbers = [1,2,3,4,5,6,7,8,9,10,12,14,15,16,17,18,25,30,31,32,33,34,62,63,64,65,66,1024,10000]
    numbers = [5,6,15,31,1024]
    #numbers = [31]
    results = []
    tmp_results = []
    rsd_results = []
    for num in numbers:
        loop_count = 10000000
        #if test_name == "sin_scalar" and num > 4:
        #    loop_count = 100000
        if num >= 8000:#10000:
            loop_count = 10000 
        elif num > 800:#1000:
            loop_count = 100000
        elif num > 60:#100:
            loop_count = 1000000
        cmd = "taskset -c 0 ./bin/{} {} {}".format(test_name, num, loop_count)
        max=0.0
        min=100000000.0
        for i in range(args.loop):
            val = run_cmd(cmd)
            if val > max:
                max = val
            if val < min:
                min = val
            tmp_results.append(val)
        print(num, max)
        print(num, min)
        #results.append(str(max))
        tmp_results.remove(max)
        tmp_results.remove(min)
        rsd_results.append(str(round(statistics.stdev(tmp_results)/statistics.mean(tmp_results)*100, 2))+"%")
        results.append(str(round(statistics.mean(tmp_results), 4)))
        tmp_results = []
    s=""
    #print(results)
    #print(rsd_results)
    #print(tmp_results)
    for i in range(len(results)):
        s+=results[i]+" "+rsd_results[i]+" "
    print(s)

if __name__ == '__main__':
    main()

