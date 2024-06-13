# net-from-scratch
(soon to be) A neural network designed to categorise MNIST digits, written in C and (hopefully) parallelised using openmp.

# running
First, the datasets must be decompressed.
```bash
./post-pull.sh
```
The project can then be built and executed.
```bash
make
./build/net
```
To clean:
```bash
make clean
```
Prior to pushing (and committing), the datasets should be compressed and the dataset.zip recreated:
```bash
./pre-push.sh
```
