/***************************************************************
This code was generated by  Spiral 5.0 beta, www.spiral.net --
Copyright (c) 2005, Carnegie Mellon University
All rights reserved.
The code is distributed under a BSD style license
(see http://www.opensource.org/licenses/bsd-license.php)

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

* Redistributions of source code must retain the above copyright
  notice, reference to Spiral, this list of conditions and the
  following disclaimer.
* Redistributions in binary form must reproduce the above
  copyright notice, this list of conditions and the following
  disclaimer in the documentation and/or other materials provided
  with the distribution.
* Neither the name of Carnegie Mellon University nor the name of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*AS IS* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************/

#include <math.h>
#include <stdlib.h>
#include "include/libfft.h"



fft_func *init_fft(int N)
{
	switch (N)
	{
		case 2:
			init_fft2();
			return fft2;
		case 4:
			init_fft4();
			return fft4;
		case 8:
			init_fft8();
			return fft8;
		case 16:
			init_fft16();
			return fft16;
		case 32:
			init_fft32();
			return fft32;
		case 64:
			init_fft64();
			return fft64;
		case 128:
			init_fft128();
			return fft128;
		case 256:
			init_fft256();
			return fft256;
		case 512:
			init_fft512();
			return fft512;
		case 1024:
			init_fft1024();
			return fft1024;
		case 2048:
			init_fft2048();
			return fft2048;
	}
	return NULL;
}


