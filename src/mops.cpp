#include "mops.hpp"
using namespace std;

/* OLD CODE - TO BE REPLACED
// turn a password into a matrices array usable for encryption
marry makePassMatrix(const string& pass) {
	// matrices array
	marry mats((pass.size()+3)/4);

	// copy the pass string over into marry
	for(int i = 0; i < pass.size(); ++i) {
	  mats[i/4][i%4] = pass[i];
	}

	// escape every matrix
	for(int i = 0; i < mats.size(); ++i) {
	  mats[i].escape();
	}

	// return matrices
	return(mats);
}

// turn any message into an array of matrices suitable for encryption
marry makeMesgMatrix(const string& mesg) {
	// matrices array
	marry mats((mesg.size()+4)/4);

	// copy the mesg over into the matrices
	for(int i = 0; i < mesg.size(); ++i) {
	  mats[i/4][i%4] = mesg[i];
	}

	// make the last character be a semicolon
	mats[mesg.size()/4][mesg.size()%4] = ';';

	// return matrices
	return(mats);
}

// encrypt marry mesg with marry pass
marry encryptMatrices(marry mesg, const marry& pass) {
	// now the fun part: let's crypt :D
	for(int i = 0; i < mesg.size(); ++i) {  // loop thru mesg
	  mesg[i] *= pass[i%pass.size()];       // multiply and store result in the mesg matrix array
	}

	// whoa, we're done!
	return(mesg);
}

// decrypt marry mesg with marry pass
marry decryptMatrices(marry mesg, const marry& pass) {
	// now the fun part: let's decrypt :D
	for(int i = 0; i < mesg.size(); ++i) {  // loop thru mesg
	  mesg[i] *= pass[i%pass.size()].inverse();// multiply with inverse
	}

	// whoa, we're done!
	return(mesg);
}

// turn two matrices into a string representation
string twoMatricesToString(const CMatrix& m1, const CMatrix& m2) {
	// the conversion temporarily converts the numbers in the matrices into a base 2 representation
	// this will be the buffer and the result
	string binpool, result;

	// tell both strings how much space to allocate
	binpool.reserve(136);
	result.reserve(17);

	// copy the first matrix into the binary pool
	for(int i = 0; i < 4; ++i) {
	  binpool += intToBinString(m1.get(i), 17);
	}
	// same with the second matrix
	for(int i = 0; i < 4; ++i) {
	  binpool += intToBinString(m2.get(i), 17);
	}
	// convert it into a string
	for(int i = 0; i < 17; ++i) {
	  result.push_back((char)binStringToInt(binpool.substr(i*8, 8))); // extract 8 chars and convert
	}

	// done :D
	return(result);
}

// turn only one matrix into a string
string oneMatrixToString(const CMatrix& mat) {
	CMatrix m2;
	return(twoMatricesToString(mat, m2));
}

// turn encrypted matrices into a string
string cryptedMatrixToString(const marry& crypt) {
	// place to store the result
	string result;
	// make space to store all the stuff
	result.reserve(((crypt.size()+1)/2) * 17);
	
	// convert all matrices to strings
	for(int i = 0; (i+1) < crypt.size(); i+=2) {
	  result.append(twoMatricesToString(crypt[i], crypt[i+1]));
	}

	if((crypt.size()%2) == 1) { // if there is an uneven number of matrices
	  result += oneMatrixToString(crypt[crypt.size()-1]); // add the last one
	}

	// return the beautiful result
	return(result);
}

// matrix encrypt
string matrixEncrypt(const std::string& mesg, const std::string& pass) {
	marry msg, pw, crypt; // matrix representation of the mesg and the password
	msg = makeMesgMatrix(mesg); // prepare mesg
	pw  = makePassMatrix(pass); // and pass
	crypt = encryptMatrices(msg, pw); // encrypt

	string enc = cryptedMatrixToString(crypt); // turn into string representation
	enc = compress_string(enc, Z_BEST_COMPRESSION);               // compress with gzip
	return encode86(enc);                     // encode86
}
*/ 

namespace cme {
	Encrypt::Encrypt(std::string password) {
		int missing = (4-(password.size()%4))%4;	// calculates how many characters are missing until the length is a multiple of 4

		for(int i = 0; i < missing; ++i) {
			// add NULLs to the pass until it's length is a multiple of 4
			password.push_back('\0');
		}

		// for every 4 characters in password
		for(int i = 0; i < (password.size() / 4); i+=4) {
			// make a new CMatrix
			CMatrix pw;

			// which is filled up with the 4 characters
			for(int j = 0; j < 4; ++j) {
				// cast to unsigned char is necessary because we don't like signs in our matrix ;)
				pw[j] = (float)(unsigned char)password[i+j];
			}

			// add this CMatrix to the list of password matrices
			passwords.push_back(pw);
		}
	}
}
