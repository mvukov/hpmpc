###################################################################################################
#                                                                                                 #
# This file is part of HPMPC.                                                                     #
#                                                                                                 #
# HPMPC -- Library for High-Performance implementation of solvers for MPC.                        #
# Copyright (C) 2014 by Technical University of Denmark. All rights reserved.                     #
#                                                                                                 #
# HPMPC is free software; you can redistribute it and/or                                          #
# modify it under the terms of the GNU Lesser General Public                                      #
# License as published by the Free Software Foundation; either                                    #
# version 2.1 of the License, or (at your option) any later version.                              #
#                                                                                                 #
# HPMPC is distributed in the hope that it will be useful,                                        #
# but WITHOUT ANY WARRANTY; without even the implied warranty of                                  #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                                            #
# See the GNU Lesser General Public License for more details.                                     #
#                                                                                                 #
# You should have received a copy of the GNU Lesser General Public                                #
# License along with HPMPC; if not, write to the Free Software                                    #
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA                  #
#                                                                                                 #
# Author: Gianluca Frison, giaf (at) dtu.dk                                                       #
#                                                                                                 #
###################################################################################################

include ../Makefile.rule

obj:
ifeq ($(TARGET), X64_AVX2)
	make -C avx2 obj
endif
ifeq ($(TARGET), X64_AVX)
	make -C avx obj
endif
ifeq ($(TARGET), X64_SSE3)
	make -C sse3 obj
endif
ifeq ($(TARGET), C99_4X4)
	make -C c99 obj
endif
ifeq ($(TARGET), CORTEX_A15)
	make -C neon obj
endif
ifeq ($(TARGET), CORTEX_A9)
	make -C neon obj
endif
ifeq ($(TARGET), CORTEX_A7)
	make -C neon obj
endif

clean:
	make -C avx2 clean
	make -C avx clean
	make -C sse3 clean
	make -C c99 clean
	make -C neon clean

