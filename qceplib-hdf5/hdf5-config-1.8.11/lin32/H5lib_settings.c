/* Generated automatically by H5make_libsettings -- do not edit */



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright by The HDF Group.                                               *
 * Copyright by the Board of Trustees of the University of Illinois.         *
 * All rights reserved.                                                      *
 *                                                                           *
 * This file is part of HDF5.  The full HDF5 copyright notice, including     *
 * terms governing use, modification, and redistribution, is contained in    *
 * the files COPYING and Copyright.html.  COPYING can be found at the root   *
 * of the source code distribution tree; Copyright.html can be found at the  *
 * root level of an installed copy of the electronic HDF5 document set and   *
 * is linked from the top-level documents page.  It can also be found at     *
 * http://hdfgroup.org/HDF5/doc/Copyright.html.  If you do not have          *
 * access to either file, you may request a copy from help@hdfgroup.org.     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Created:		Apr  3, 2014
 *			mockbuild@weimar.xray.aps.anl.gov
 *
 * Purpose:		This machine-generated source code contains
 *			information about the library build configuration
 *
 * Modifications:
 *
 *	DO NOT MAKE MODIFICATIONS TO THIS FILE!
 *	It was generated by code in `H5make_libsettings.c'.
 *
 *-------------------------------------------------------------------------
 */

char H5libhdf5_settings[]=
	"	    SUMMARY OF THE HDF5 CONFIGURATION\n"
	"	    =================================\n"
	"\n"
	"General Information:\n"
	"-------------------\n"
	"		   HDF5 Version: 1.8.11\n"
	"		  Configured on: Thu Apr  3 15:57:41 CDT 2014\n"
	"		  Configured by: mockbuild@\n"
	"		 Configure mode: production\n"
	"		    Host system: i686-redhat-linux-gnu\n"
	"	      Uname information: Linux weimar.xray.aps.anl.gov 3.13.7-200.fc20.x86_64 #1 SMP Mon Mar 24 22:01:49 UTC 2014 i686 i686 i386 GNU/Linux\n"
	"		       Byte sex: little-endian\n"
	"		      Libraries: static, shared\n"
	"	     Installation point: /usr\n"
	"\n"
	"Compiling Options:\n"
	"------------------\n"
	"               Compilation Mode: production\n"
	"                     C Compiler: /usr/lib/ccache/gcc ( gcc (GCC) 4.8.2 20131212 )\n"
	"                         CFLAGS: -O0 -g -pipe -Wall -Wp,-D_FORTIFY_SOURCE=2 -fexceptions -fstack-protector-strong --param=ssp-buffer-size=4 -grecord-gcc-switches  -m32 -march=i686 -mtune=atom -fasynchronous-unwind-tables\n"
	"                      H5_CFLAGS: -std=c99 -pedantic -Wall -Wextra -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wcast-qual -Wcast-align -Wwrite-strings -Wconversion -Waggregate-return -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wnested-externs -Winline -Wfloat-equal -Wmissing-format-attribute -Wmissing-noreturn -Wpacked -Wdisabled-optimization -Wformat=2 -Wendif-labels -Wdeclaration-after-statement -Wold-style-definition -Winvalid-pch -Wvariadic-macros -Winit-self -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wunused-macros -Wunsafe-loop-optimizations -Wc++-compat -Wstrict-overflow -Wlogical-op -Wlarger-than=2048 -Wvla -Wsync-nand -Wframe-larger-than=16384 -Wpacked-bitfield-compat -Wstrict-overflow=5 -Wjump-misses-init -Wunsuffixed-float-constants -Wdouble-promotion -Wsuggest-attribute=const -Wtrampolines -Wstack-usage=8192 -Wvector-operation-performance -O3 -fomit-frame-pointer -finline-functions\n"
	"                      AM_CFLAGS: \n"
	"                       CPPFLAGS: \n"
	"                    H5_CPPFLAGS: -D_POSIX_C_SOURCE=199506L   -DNDEBUG -UH5_DEBUG_API\n"
	"                    AM_CPPFLAGS: -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_BSD_SOURCE \n"
	"               Shared C Library: yes\n"
	"               Static C Library: yes\n"
	"  Statically Linked Executables: no\n"
	"                        LDFLAGS: -Wl,-z,relro \n"
	"                     H5_LDFLAGS: \n"
	"                     AM_LDFLAGS: \n"
	" 	 	Extra libraries:  -lz -ldl -lm \n"
	" 		       Archiver: ar\n"
	" 		 	 Ranlib: ranlib\n"
	" 	      Debugged Packages: \n"
	"		    API Tracing: no\n"
	"\n"
	"Languages:\n"
	"----------\n"
	"                        Fortran: yes\n"
	"               Fortran Compiler: /usr/bin/gfortran ( GNU Fortran (GCC) 4.8.2 20131212 )\n"
	"          Fortran 2003 Compiler: yes\n"
	"                  Fortran Flags: -O2 -g -pipe -Wall -Wp,-D_FORTIFY_SOURCE=2 -fexceptions -fstack-protector-strong --param=ssp-buffer-size=4 -grecord-gcc-switches  -m32 -march=i686 -mtune=atom -fasynchronous-unwind-tables -I/usr/lib/gfortran/modules\n"
	"               H5 Fortran Flags:  \n"
	"               AM Fortran Flags:  -O2 -g -pipe -Wall -Wp,-D_FORTIFY_SOURCE=2 -fexceptions -fstack-protector-strong --param=ssp-buffer-size=4 -grecord-gcc-switches  -m32 -march=i686 -mtune=atom -fasynchronous-unwind-tables -I/usr/lib/gfortran/modules\n"
	"         Shared Fortran Library: yes\n"
	"         Static Fortran Library: yes\n"
	"\n"
	"                            C++: yes\n"
	"                   C++ Compiler: /usr/lib/ccache/g++ ( g++ (GCC) 4.8.2 20131212 )\n"
	"                      C++ Flags: -O2 -g -pipe -Wall -Wp,-D_FORTIFY_SOURCE=2 -fexceptions -fstack-protector-strong --param=ssp-buffer-size=4 -grecord-gcc-switches  -m32 -march=i686 -mtune=atom -fasynchronous-unwind-tables\n"
	"                   H5 C++ Flags:  \n"
	"                   AM C++ Flags: \n"
	"             Shared C++ Library: yes\n"
	"             Static C++ Library: yes\n"
	"\n"
	"Features:\n"
	"---------\n"
	"                  Parallel HDF5: no\n"
	"             High Level library: yes\n"
	"                   Threadsafety: no\n"
	"            Default API Mapping: v18\n"
	" With Deprecated Public Symbols: yes\n"
	"         I/O filters (external): deflate(zlib)\n"
	"         I/O filters (internal): shuffle,fletcher32,nbit,scaleoffset\n"
	"                            MPE: no\n"
	"                     Direct VFD: no\n"
	"                        dmalloc: no\n"
	"Clear file buffers before write: yes\n"
	"           Using memory checker: no\n"
	"         Function Stack Tracing: no\n"
	"                           GPFS: no\n"
	"      Strict File Format Checks: no\n"
	"   Optimization Instrumentation: no\n"
	"       Large File Support (LFS): yes\n"
;

