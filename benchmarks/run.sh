# !/bin/sh
./run_test.py --func sin --name scalar_vec --loop 10
./run_test.py --func sin --name vector --loop 10
./run_test.py --func cos --name scalar_vec --loop 10
./run_test.py --func cos --name vector --loop 10
./run_test.py --func powf --name scalar_vec --loop 10
./run_test.py --func powf --name vector --loop 10
./run_test.py --func sincos --name scalar_vec --loop 10
./run_test.py --func sincos --name vector --loop 10
