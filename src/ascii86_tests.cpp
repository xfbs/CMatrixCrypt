#include <iostream>
#include <string>
#include <cassert>
#include <ctime>
#include "ascii86.hpp"
using namespace std;

void encode_tests();
void encode_test_words();
void encode_test_sentences();
void encode_test_inputs();
void encode_test_outputs();
void encode_test_misc();
void decode_tests();
void decode_test_words();
void decode_test_sentences();
void decode_test_inputs();
void decode_test_outputs();
void decode_test_misc();

int main(void) {
  clock_t start = clock();
  cout.setf(ios_base::fixed);
  encode_tests();
  decode_tests();
  clock_t end = clock();
  double time = difftime(end, start) / CLOCKS_PER_SEC;
  cout << "tests took " << time << " seconds" << endl;
}

void encode_tests() {
  cout << "encode test words" << endl;
  encode_test_words();
  cout << "encode test sentences" << endl;
  encode_test_sentences();
  cout << "encode test inputs" << endl;
  encode_test_inputs();
  cout << "encode test outputs" << endl;
  encode_test_outputs();
  cout << "encode test misc" << endl;
  encode_test_misc();
}

void decode_tests() {
  cout << "decode test words" << endl;
  decode_test_words();
  cout << "decode test sentences" << endl;
  decode_test_sentences();
  cout << "decode test inputs" << endl;
  decode_test_inputs();
  cout << "decode test outputs" << endl;
  decode_test_outputs();
  cout << "decode test misc" << endl;
  decode_test_misc();
}

void encode_test_words() {
  cme::Encode86 enc;
  std::string word;
  
  enc << "Working";
  enc.close();
  enc >> word;
  assert(word == "<~=)W+pBl7P~>");
  enc.reset(); word.clear();

  enc << "state";
  enc.close();
  enc >> word;
  assert(word == "<~F*(i4AH~>");
  enc.reset(); word.clear();
}

void encode_test_sentences() {
  cme::Encode86 enc;
  std::string sentence;

  enc << "Working state";
  enc.close();
  enc >> sentence;
  assert(sentence == "<~=)W+pBl7Q+F*(i4AH~>");
  enc.reset(); sentence.clear();

  enc << "Uptime is valuable";
  enc.close();
  enc >> sentence;
  assert(sentence == "<~<H*%oD.Oi(F!,X7Cis/qCh3~>");
  enc.reset(); sentence.clear();
}

void encode_test_inputs() {
  cme::Encode86 enc;
  std::string input;

  enc << "He";
  enc.write("ll");
  enc.put('o');
  enc.close();
  enc >> input;
  assert(input == "<~87cURDZ~>");
}

void encode_test_outputs() {
  cme::Encode86 enc;
  std::string test = "Test case";
  std::string result;

  for(int i = 0; i < test.size(); ++i) {
    enc.put(test[i]);
    result += enc.read();
  }
  enc.close();
  result += enc.read();

  assert(result == enc.data());
  assert(result == "<~<+U,m+Cei$AH~>");
  enc.reset(); result.clear();
  
  enc << test;
  enc.close();
  char chr;
  while((chr=enc.get()) && chr!='\0') {
    result.push_back(chr);
  }

  assert(result == "<~<+U,m+Cei$AH~>");
}

void encode_test_misc() {
  cme::Encode86 enc;

  enc << "test";
  assert(enc.closed() == false);
  enc.close();
  assert(enc.closed() == true);

  assert(enc.data() == "<~FCfN8~>");
  enc.reset();
  assert(enc.closed() == false);
}

void decode_test_words() {
  cme::Decode86 dec;
  
  dec << "<~6Xb%I~>";
  assert(dec.data() == "Case");
  dec.reset();

  dec << "<~F*)P8Gl~>";
  assert(dec.data() == "study");
  dec.reset();
}

void decode_test_sentences() {
  cme::Decode86 dec;

  dec << "<~6Xb%I+EMXIA9e~>";
  assert(dec.data() == "Case study");
  dec.reset();

  dec << "<~:iCPhEZfIBDesI~>";
  assert(dec.data() == "Power tools");
  dec.reset();
}

void decode_test_inputs() {
  cme::Decode86 dec;
  std::string text = "b'4~>";

  dec << "<~6#";
  dec.write("L=UGp$R1E");
  for(int i = 0; i < text.size(); ++i) {
    dec.put(text[i]);
  }

  assert(dec.data() == "Angry birds");
}

void decode_test_outputs() {
  cme::Decode86 dec;
  std::string enc = "<~7:C7ZATDZ2Eb0E4Cisi6Df,~>";
  std::string orig;

  for(int i = 0; i < enc.size(); ++i) {
    dec.put(enc[i]);
  }

  while(!dec.eol()) {
    orig.push_back(dec.get());
  }

  assert(orig == "Eastern revolution");
  dec.reset(); orig.clear();

  dec << "<~7:C7ZATDZ2";
  orig += dec.read();
  dec << "Eb0E4Cisi6Df,~>";
  orig += dec.read();

  assert(orig == "Eastern revolution");
  dec.reset(); orig.clear();
}

void decode_test_misc() {
  cme::Decode86 dec;

  assert(dec.closed() == false);
  dec << "<~7:C7ZATDZ2Eb0E4Cisi6Df,~>";
  assert(dec.closed() == true);

  assert(dec.eol() == false);
  dec.read();
  assert(dec.eol() == true);
}
