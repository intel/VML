DISCONTINUATION OF PROJECT

This project will no longer be maintained by Intel.

Intel has ceased development and contributions including, but not limited to, maintenance, bug fixes, new releases, or updates, to this project.  

Intel no longer accepts patches to this project.

If you have an ongoing need to use this project, are interested in independently developing it, or would like to maintain patches for the open source software community, please create your own fork of this project.  

Contact: webadmin@linux.intel.com
# Vectorized Math Library (VML)
It is a performance-driven header only library providing a set of functions doing basic math operations like sin/cos/exp/etc..It leverages vectorization instructions (SSE/AVX/AVX512) on IA platforms to achieve best performance on Intel hardware. It provides pure C APIs which can support both C and C++.

## How to use it
- Download the vml source to anywhere you want. Suppose the directory is <vml_root_dir>
- Update your code, find the place where you want to call the vectorized function, then include "vml_math.h".
- Add -I<vml_root_dir> in your CFLAGS and "-lm" in your LDFLAGS.

## API types
It provides two groups of APIs, one group is "vml_xxx" and the other one is "vml_xxx_hook". The only difference for them is that the latter APIs have extra 4 parameters "vml_hook_func_t pre_hook, void * pre_hook_args, vml_hook_func_t post_hook, void * post_hook_args". It gives user a chance to call hook functions before or after each single vectorization calculation.

Pseudo-code:
```
for(int i=0; i<N; i++>)
{
    pre_hook(pre_hook_args);
    _ZGVeN8v_sin(...);
    post_hook(post_hook_args);
}
```
You can also refer to "examples".

## About security
If you have any problems about security, please contact security@intel.com.
