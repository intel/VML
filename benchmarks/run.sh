# !/bin/sh
./run_test.py --func sinf --name scalar --loop 10
./run_test.py --func sinf --name scalar_vec --loop 10
./run_test.py --func sinf --name vector --loop 10
