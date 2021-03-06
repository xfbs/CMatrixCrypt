/*  File: sha4_tests.cpp
 *  
 *  Copyright (C) 2011, Patrick M. Elsen
 *
 *  This file is part of CMatrixCrypt (http://github.com/xfbs/CMatrixCrypt)
 *  Author: Patrick M. Elsen <pelsen.vn (a) gmail.com>
 *
 *  All rights reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "polarssl/sha4.h"
#include <string>
#include <iostream>
#include <cassert>
#include <ctime>

using namespace std;

void test_manual_hashsum();
void test_auto_hashsum();
void test_multiple_inputs();
void test_file_input();

int main() {
	// start timer
  clock_t start = clock();
	
	// testing code
	cout << "testing manual hashsum" << endl;
	test_manual_hashsum();
	cout << "testing auto hashsum" << endl;
	test_auto_hashsum();
	cout << "testing multiple inputs" << endl;
	test_multiple_inputs();
	cout << "testing file input" << endl;
	test_file_input();

	// stop timer
  clock_t end = clock();
	// get difference
  double time = difftime(end, start) / CLOCKS_PER_SEC;
	// set cout to show all digits of floating point numbers
  cout.setf(std::ios_base::fixed);
	// reveal the time taken
  cout << "tests took " << time << " seconds" << endl;
}

void test_multiple_inputs() {
	// sample data
	string uh("this is raw");
	string oh(" data");

	// new sha4 context
  polarssl::sha4_context con;
	// initialize to SHA512
  polarssl::sha4_starts(&con, 0);
  
	// start hashing
	polarssl::sha4_update(&con, (const unsigned char *) uh.c_str(), uh.size());
	// and do some more hashing
	polarssl::sha4_update(&con, (const unsigned char *) oh.c_str(), oh.size());

	// char array to store the output
  unsigned char output[64];
  polarssl::sha4_finish(&con, (unsigned char *) output);

	const unsigned char example[64] = 
	{ 0x52, 0x8d, 0xd5, 0x2a, 0x6a, 0x4d, 0x16, 0x27, 
		0x2b, 0x31, 0xcd, 0x92, 0x32, 0x36, 0x57, 0x9f, 
		0xf4, 0x53, 0xda, 0x18, 0x13, 0x10, 0x3f, 0xf7, 
		0x7e, 0x4e, 0x68, 0x7e, 0x22, 0x36, 0xb1, 0x40, 
		0x97, 0x70, 0x6c, 0x6e, 0x11, 0xed, 0x78, 0x6f, 
		0x0b, 0x65, 0xcd, 0xd5, 0x5a, 0x90, 0x24, 0x83, 
		0x42, 0x96, 0x43, 0x4e, 0x06, 0xc9, 0xd1, 0xac, 
		0x7f, 0x42, 0x18, 0xe3, 0x59, 0xf2, 0x23, 0x3d	};

	for(int i = 0; i < 64; ++i) {
		assert(output[i] == example[i]);
	}
}

void test_manual_hashsum() {
	// sample data
	string uh("this is raw data");

	// new sha4 context
  polarssl::sha4_context con;
	// initialize to SHA512
  polarssl::sha4_starts(&con, 0);
  
	// start hashing
	polarssl::sha4_update(&con, (const unsigned char *) uh.c_str(), uh.size());

	// char array to store the output
  unsigned char output[64];
  polarssl::sha4_finish(&con, (unsigned char *) output);

	const unsigned char example[64] = 
	{ 0x52, 0x8d, 0xd5, 0x2a, 0x6a, 0x4d, 0x16, 0x27, 
		0x2b, 0x31, 0xcd, 0x92, 0x32, 0x36, 0x57, 0x9f, 
		0xf4, 0x53, 0xda, 0x18, 0x13, 0x10, 0x3f, 0xf7, 
		0x7e, 0x4e, 0x68, 0x7e, 0x22, 0x36, 0xb1, 0x40, 
		0x97, 0x70, 0x6c, 0x6e, 0x11, 0xed, 0x78, 0x6f, 
		0x0b, 0x65, 0xcd, 0xd5, 0x5a, 0x90, 0x24, 0x83, 
		0x42, 0x96, 0x43, 0x4e, 0x06, 0xc9, 0xd1, 0xac, 
		0x7f, 0x42, 0x18, 0xe3, 0x59, 0xf2, 0x23, 0x3d	};

	for(int i = 0; i < 64; ++i) {
		assert(output[i] == example[i]);
	}
}

void test_auto_hashsum() {
	// data to hash
	unsigned char data[] = "jingle bells";
  // where to store hashed data
	unsigned char hash[64];

	// let's make the magic happen
	polarssl::sha4(data, 12, hash, 0);

	unsigned char real[64] = 
	{	0xb8, 0x70, 0xed, 0x10, 0x3e, 0xd1, 0xee, 0xbb, 
		0xf2, 0x2e, 0x51, 0x62, 0x86, 0xfc, 0x00, 0xa7, 
		0xff, 0x60, 0xce, 0xa4, 0xc0, 0x7a, 0x24, 0x17, 
		0xfc, 0xf1, 0x59, 0x35, 0x9e, 0x7f, 0x15, 0x29, 
		0xd9, 0x3c, 0xf3, 0xd1, 0xa9, 0x19, 0x71, 0x98, 
		0xc4, 0x9b, 0x36, 0x71, 0xc0, 0xb3, 0xce, 0x64, 
		0x92, 0xaf, 0x3e, 0xa4, 0x53, 0x6e, 0x39, 0xf5, 
		0xd1, 0x06, 0x71, 0x02, 0x4e, 0x83, 0x82, 0x76	};

	for(int i = 0; i < 64; ++i) {
		assert(hash[i] == real[i]);
	}
}

void test_file_input() {
	// i powtpwned writing this test ;)
}
