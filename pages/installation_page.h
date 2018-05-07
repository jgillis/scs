/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Pantelis Sopasakis (https://alphaville.github.io),
 *                    Krina Menounou (https://www.linkedin.com/in/krinamenounou), 
 *                    Panagiotis Patrinos (http://homes.esat.kuleuven.be/~ppatrino)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 */
/*! \page page_installation Installation
 * 
 * \tableofcontents
 * 
 * \section sec-interfaces Interfaces
 * 
 * \subsection dependencies_superscs Dependencies
 * 
 * Before you proceed, make sure the following dependencies are installed: 
 * 
 * - <code>libblas-dev</code>
 * - <code>liblapack-dev</code>
 * - <code>python-numpy</code>
 * - <code>python-scipy</code>
 * 
 * In Linux run <code>sudo apt-get install libblas-dev liblapack-dev 
 * python-numpy python-scipy</code>.
 * 
 * \subsection installation_in_c Linux and MacOSX
 *
 * 
 * First, you need to [download SuperSCS](https://github.com/kul-forbes/scs/archive/master.zip)
 * from the [github repo](https://github.com/kul-forbes/scs) of SuperSCS, or use the 
 * command:
 * 
 *     git clone https://github.com/kul-forbes/scs.git
 *     cd scs/
 * 
 * Installation runs as simple as 
 * 
 *     make
 * 
 * Once \c make finishes, the library files will be in <code>out/</code>.
 *  
 * If you want to run the tests, do 
 *
 *     make run-test
 *
 * 
 * If, additionally, you want to run the tests and perform a memory check
 * using [valgrind](http://valgrind.org), do 
 * 
 *     make run-test-mem
 * 
 * 
 * For more advanced options, type in your terminal 
 * 
 *     make help
 * 
 * \subsection sec_matlab MATLAB
 * 
 * To install <code>SuperSCS</code> in MATLAB, you need to build a MEX interface.
 * 
 * Do:
 *
 * \code{.cpp}
 *  cd matlab;
 *  make_scs;
 * \endcode
 * 
 * This should work. If not, please [report an issue](https://github.com/kul-forbes/scs/issues).
 * 
 * 
 * 
 * \subsection sec_cvx_matlab CVX MATLAB
 * 
 * Necessary steps:
 * 
 * - Download and unpack <code>CVX 3.0</code> from [here](http://cvxr.com/cvx/beta/)
 * - You need to do a tiny modification in [<code>cvx/shims/cvx_scs.m</code>](https://gist.github.com/alphaville/13d059b67166997eef9947e91ce5d714)
 *   and comment-out lines 165-175. 
 *   Find the modified file [here](https://gist.github.com/alphaville/13d059b67166997eef9947e91ce5d714).
 * - Navigate to the <code>cvx</code> directory
 * - Run <code>cvx_setup</code>
 * - To use <code>SuperSCS</code>, we call <code>cvx</code> with <code>cvx_solver scs</code>
 *   and setting the parameter <code>do_super_scs</code> to 1.
 * 
 * Here is an example of an LP problem
 * ~~~~~{.m}
 * A(1,1) = 0.3; A(4,1) = -0.5;
 * A(2,2) = 0.7; A(4,2) =  0.9; A(3,3) = 0.2;
 * A = sparse(A);
 * n = size(A,2);
 * b = [0.2; 0.1; -0.1; 0.1];
 * c = [1;-2;-3];
 * 
 * cvx_begin
 *     cvx_solver scs
 *     cvx_solver_settings('eps', 1e-8, 'do_super_scs', 1, 'rho_x', 1,...
 *          'direction', 100, 'memory', 50);
 *     variable x(n);
 *     dual variable y;
 *     minimize( x'*x + c' * x );
 *     subject to
 *          y : A * x <= b;
 * cvx_end
 *~~~~~
 * 
 * We have chosen the SuperSCS mode with \f$\rho_x=1\f$, the restarted Broyden 
 * direction and memory equal to \f$50\f$.
 * 
 * We have set the tolerance to \f$10^{-8}\f$.
 * 
 * In case you encounter any problems, please [report an issue](https://github.com/kul-forbes/scs/issues).
 * 
 * \note This a pre-alpha unstable version, so there might be issues. 
 * 
 * \note For example, <code>cvx_precision</code> is not supported (you have to use 
 * <code>cvx_solver_settings('eps',...)</code>).
 * 
 * 
 * \subsection sec_installation_python Python
 * 
 * In order to install the SuperSCS module for Python, cd to python/ and
 * run setup.py with the argument install:
 * 
 * ~~~~~{.sh}
 * cd python/
 * (sudo) python setup.py install
 * ~~~~~
 * 
 * You will then be able to import \c superscs into your Python code. 
 * 
 * Further documentation for the Python module can be found \ref secpython "here".
 * 
 * 
 * \subsection sec_compiling_superscs_in_c SuperSCS: Compiling & Linking in C
 * 
 * Read this section if you intend to use SuperSCS in C.
 * 
 * Most users are interested
 * in use SuperSCS via its MATLAB and Python interface and via CVX/CVXPy.
 * 
 * To you SuperSCS in C you first need to 
 * \ref installation_in_c "build the source code" as explained above.
 * 
 * This will generate the following four files in the <code>out/</code> folder:
 * 
 * - **Static library files:**
 *      - <code>out/libscsdir.a</code>: static SuperSCS library with the direct method
 *      - <code>out/libscsindir.a</code>: static SuperSCS library with the indirect 
 *                                        method (more suitable for large-scale problems).
 * - **Shared library files:**
 *      - <code>out/libscsdir.so</code>: shared library (direct)
 *      - <code>out/libscsindir.so</code>: shared library (indirect)
 * 
 * Let us give a brief example of how to use SuperSCS in C by compiling your source
 * code (read more \ref page_save_load "here")...
 * 
 * ~~~~~
 * // FILE: superscs_test.c 
 * 
 * #include <stdio.h>
 * #include <stdlib.h>
 * #include "scs.h"
 * 
 * int main(int argc, char** argv) {
 *     ScsData * data = SCS_NULL;
 *     ScsCone * cone = SCS_NULL;
 *     ScsInfo * info = scs_init_info();
 *     ScsSolution * sol = scs_init_sol();
 *     const char * filepath = "path/to/my_problem.yml";
 *     scs_int status;
 * 
 *     // load problem from file
 *     status = scs_from_YAML(filepath, &data, &cone);
 * 
 *     // solver options
 *     data->stgs->do_super_scs = 1;
 *     data->stgs->direction = restarted_broyden;
 *     data->stgs->memory = 100;
 *     data->stgs->verbose = 1;
 * 
 *     // solve the problem
 *     status = scs(data, cone, sol, info);
 * 
 *     // free allocated memory
 *     scs_free_data_cone(data, cone);
 *     scs_free_info(info);
 *     scs_free_sol(sol);
 * 
 *     return (EXIT_SUCCESS);
 * }
 * ~~~~~
 * 
 * Let us now compile and link to the static library <code>out/libscsdir.a</code>
 * 
 * ~~~~~
 * # On Windows and MacOSX
 * gcc -Iinclude superscs_test.c \
 *   -o superscs_test path/to/libscsindir.a \
 *   -llapack -lblas -lm
 * ~~~~~
 * 
 * On Linux, append <code>-lrt</code>, that is
 * 
 * ~~~~~
 * # On Linux
 * gcc -Iinclude superscs_test.c \
 *   -o superscs_test path/to/libscsindir.a \
 *   -llapack -lblas -lm -lrt
 * ~~~~~
 * 
 * In particular:
 * 
 * - <b>-Lpath/to/out/superscs/lib/dir</b> specifies the path to the SuperSCS library 
 *   where <b>libscsindir.a</b> is stored. You must have run <b>make</b> for this to 
 *   exist.
 * - <b>-l:libscsindir.a</b> means that the linker should link to the SuperSCS library
 *   statically. 
 * - <b>-llapack -lblas</b> these are the <a href="http://www.netlib.org/blas/">blas</a> 
 *   and <a href="http://www.netlib.org/lapack/">lapack</a> linear algebra libraries.
 * - <b>-lm -lrt</b> these are the math and real-time libraries; the latter is 
 *   optional.
 */