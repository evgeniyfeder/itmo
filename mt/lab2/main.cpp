#include <iostream>
#include <string>
#include <locale>
#include <unordered_map>
#include <memory>

/* Grammatic
 *
 * 1. not
 * 2. and
 * 3. xor
 * 4. or
 * 
 * S -> S or  A | A
 * A -> A xor B | B
 * B -> B and C | C
 * C -> not C   | D 
 * D -> [a-z]   |(S)
 * 
 * S  -> S'
 * S' -> AS*
 * S* -> or AS*  | eps
 * A  -> BA*              
 * A* -> xor BA* | eps
 * B  -> CB*
 * B* -> and CB* | eps
 * C  -> not C   | D
 * D  -> LETTER  | (S')
 *  
 *          FIRST           | FOLLOW
 * S  { not, LETTER, ( }    | { $ }
 * S' { not, LETTER, ( }    | { $, ) }
 * S* { or, $ }             | { $, ) }
 * A  { not, LETTER, ( }    | { or, $, ) }  
 * A* { xor, $ }            | { or, $, ) }
 * B  { not, LETTER, ( }    | { xor, or, $, ) }
 * B* { and, $ }            | { xor, or, $, ) }
 * C  { not, LETTER, ( }    | { and, xor, or, $, ) }
 * D  { LETTER, ( }         | { and, xor, or, $, ) }
 *   
 */

enum class Token {
   VAR, AND, OR, XOR, NOT, LPAREN, RPAREN, END
};

class Lexer {
private:
   std::string string;
   std::string::const_iterator iter;
   
   std::unordered_map<std::string, Token> tokenStrings = 
   {
      {"and", Token::AND},
      {"xor", Token::XOR},
      {"or",  Token::OR},
      {"not", Token::NOT},
   };

   std::unordered_map<char, Token> tokenChars = 
   {
      {'(', Token::LPAREN},
      {')', Token::RPAREN},
      {'$', Token::END}
   };

   Token curToken = Token::AND;
   std::string curStr;

   void UpdateToken() {
      while (iter != string.end() && *iter == ' ') {
         iter++;
      }

      char curSym = *iter;

      // check for words
      if (islower(curSym)) {
         std::string word;

         while (iter != string.end() && islower(*iter)) {
            word.push_back(*iter++);
         }
         curStr = word;
         auto resFind = tokenStrings.find(word);
         if (resFind != tokenStrings.end()) {
            curToken = resFind->second;
         }
         else if (word.size() == 1) {
            curToken = Token::VAR;
         }
         else {
            throw std::exception(("LEXER ERROR: Unknown word " + word).c_str());
         }
         return;
      }

      auto resFind = tokenChars.find(curSym);
      if (resFind != tokenChars.end()) {
         iter++;
         curStr = curSym;
         curToken = resFind->second;
      }
      else {
         throw std::exception((std::string("LEXER ERROR: Unknown character ") + curSym).c_str());
      }
   }
public:
   void UpdateString(const std::string& str) { string = str; iter = string.cbegin(); UpdateToken(); }

   
   void NextToken () {
      // iter++;
      UpdateToken();
   }

   Token GetToken() const { return curToken; }

   Token GetAndNextToken () {
      const Token curToken = GetToken();
      NextToken();
      return curToken;
   }

   size_t GetPosition() const { return iter - string.cbegin(); }
   std::string GetTokenStr() const { return curStr; }
};

struct Tree {
   using vec_type = std::vector<Tree*>;
   vec_type children;
   std::string name;

   Tree (std::string &&name, vec_type &&children = vec_type())
      : children(std::move(children)), 
        name(std::move(name))
   {
   }

   ~Tree() {
      for (auto &&c : children) {
         delete c;
      }
   }
private:
   void PrintRec(size_t indent) {
      for (size_t i = 0; i < indent; i++) { std::cout << ' '; }
      std::cout << name << std::endl;
      for (auto &&c : children) {
         c->PrintRec(indent + 2);
      }
   }

public:
   void Print() {
      PrintRec(0);
   }
};

class Parser {
   Lexer lex;

   Tree * D() {
      Token curToken = lex.GetToken();
      Tree * sRes;
      std::string curName;
      switch (curToken) {
      case Token::VAR:
         curName = lex.GetTokenStr();
         lex.NextToken();
         return new Tree(std::move(curName));
      case Token::LPAREN:
         lex.NextToken();
         sRes = S();
         
         if (lex.GetToken() != Token::RPAREN) {
            throw std::exception(("PARSER ERROR: Expected ')' at position " + std::to_string(lex.GetPosition())).c_str());
         }

         lex.NextToken();
         return sRes;
      default:
         throw std::exception((std::string("PARSER ERROR: Unexpected token '") + lex.GetTokenStr() + "' at position " + std::to_string(lex.GetPosition()) + " . Waiting for var or lparent").c_str());

      }
   }

   Tree * C() {
      Token curToken = lex.GetToken();
      bool isNegate = false;
      Tree * cdRes;
      switch (curToken) {
      case Token::NOT:
         isNegate = true;
         lex.NextToken();
         cdRes = C();
         return new Tree("not", std::vector<Tree *>({ cdRes }));
      case Token::VAR:
      case Token::LPAREN:
         return D();
      default:
         throw std::exception((std::string("PARSER ERROR: Unexpected token '") + lex.GetTokenStr() + "' at position " + std::to_string(lex.GetPosition()) + " . Waiting for not, var or lparent").c_str());

      }
   }

   Tree * BPrime() {
      Token curToken = lex.GetToken();
      Tree * cRes;
      Tree * bPrimeRes;

      switch (curToken) {
      case Token::AND:
         lex.NextToken();

         cRes = C();
         bPrimeRes = BPrime();

         if (bPrimeRes) {
            return new Tree("and", std::vector<Tree *>({ cRes, bPrimeRes }));
         }
         else {
            return cRes;
         }
         break;
      default:
         return nullptr;
      }

   }


   Tree * B() {
      Token curToken = lex.GetToken();
      Tree * cRes;
      Tree * bPrimeRes;

      switch (curToken) {
      case Token::NOT:
      case Token::VAR:
      case Token::LPAREN:
         cRes = C();
         bPrimeRes = BPrime();

         if (bPrimeRes) {
            return new Tree("and", std::vector<Tree *>({ cRes, bPrimeRes }));
         }
         else {
            return cRes;
         }

         break;
      default:
         throw std::exception((std::string("PARSER ERROR: Unexpected token '") + lex.GetTokenStr() + "' at position " + std::to_string(lex.GetPosition()) + " . Waiting for not, var or lparent").c_str());

      }
   }


   Tree * APrime() {
      Token curToken = lex.GetToken();
      Tree * bRes;
      Tree * aPrimeRes;

      switch (curToken) {
      case Token::XOR:
         lex.NextToken();

         bRes = B();
         aPrimeRes = APrime();

         if (aPrimeRes) {
            return new Tree("xor", std::vector<Tree *>({ bRes, aPrimeRes }));
         } else {
            return bRes;
         }
      default:
         return nullptr;
      }

   }


   Tree * A() {
      Token curToken = lex.GetToken();
      Tree * bRes;
      Tree * aPrimeRes;

      switch (curToken) {
      case Token::NOT:
      case Token::VAR:
      case Token::LPAREN:
         bRes = B();
         aPrimeRes = APrime();

         if (aPrimeRes) {
            return new Tree("xor", std::vector<Tree *>({ bRes, aPrimeRes }));
         }
         else {
            return bRes;
         }
      default:
         throw std::exception((std::string("PARSER ERROR: Unexpected token '") + lex.GetTokenStr() + "' at position " + std::to_string(lex.GetPosition()) + " . Waiting for not, var or lparent").c_str());
         
      }
   }


   Tree * SPrime() {
      Token curToken = lex.GetToken();
      Tree * aRes;
      Tree * sPrimeRes;

      switch (curToken) {
      case Token::OR:
         lex.NextToken();

         aRes = A();
         sPrimeRes = SPrime();

         if (sPrimeRes) {
            return new Tree("or", std::vector<Tree *>({aRes, sPrimeRes}));
         } else {
            return aRes;
         }
      default:
         return nullptr;
      }

   }

   Tree * S() {
      Token curToken = lex.GetToken();
      Tree * aRes;
      Tree * sPrimeRes;

      switch (curToken) {
      case Token::NOT:
      case Token::VAR:
      case Token::LPAREN:
         aRes = A();
         sPrimeRes = SPrime();

         if (sPrimeRes) {
            return new Tree("or", std::vector<Tree *>({ aRes, sPrimeRes }));
         } else {
            return aRes;
         }
         break;
      default:
         throw std::exception((std::string("PARSER ERROR: Unexpected token '") + lex.GetTokenStr() + "' at position " + std::to_string(lex.GetPosition()) + " . Waiting not, var or lparent").c_str());
      }
      
   }

public:
   void UpdateString (const std::string& str) { lex.UpdateString(str + '$'); }
   
   Tree* parse () {
      Tree *Sres = S();
      if (lex.GetToken() != Token::END) {
         throw std::exception((std::string("PARSER ERROR: Unexpected token '") + lex.GetTokenStr() + "' at position " + std::to_string(lex.GetPosition())).c_str());
      }
      return Sres;
   }
};


bool check_eq(Tree *a, Tree *b) {
   if (a->name != b->name || a->children.size() != b->children.size()) { return false; }

   bool result = true;
   for (size_t i = 0; i < a->children.size(); i++) {
      result &= check_eq(a->children[i], b->children[i]);
   }
   return result;
}
void test_size(size_t numIter) {

   std::cout << "Test size: " + std::to_string(numIter) + "... ";

   std::string input = "x";
   Tree *ans = new Tree("x", {});

   for (size_t i = 0; i < numIter; i++) {
      int opt = rand() % 4;
      char var = char('a' + rand() % 26);
      std::string op;

      if (opt == 0) {
         input = "(not " + input + ")";
         ans = new Tree("not", { ans });
      } else {
         int swap = rand() % 2;

         switch (opt) {
         case 1:
            op = "or";
            break;
         case 2:
            op = "and";
            break;
         case 3:
            op = "xor";
            break;
         }

         if (swap) {
            input = "(" + input + " " + op + " " + var + ")";
            ans = new Tree("or", { ans, new Tree(std::string(1, var), {}) });
         } else {
            input = "(" + std::string(1, var) + " " + op + " " + input + ")";
            ans = new Tree("or", { new Tree(std::string(1, var), {}), ans });
         }
      }
   }
   Parser p;
   p.UpdateString(input);

   if (check_eq(ans, p.parse())) {
      delete ans;
      throw std::exception(("Incorrect result in size test: " + input).c_str());
   }
   std::cout << "OK. Test: " + input << std::endl;
   delete ans;
}

void priority_test() {
   std::cout << "=============== PRIORITY TEST =======================" << std::endl;
   Parser p;
   std::string input = "not (not a and b and (c or d xor e))";
   p.UpdateString(input);
   Tree * res = p.parse();
   std::cout << input << std::endl;
   res->Print();
   delete res;
}

void correct_test(const std::string & input) {
   std::cout << "Correct test: " + input + " ... ";

   Parser p;
   p.UpdateString(input);
   Tree * res = p.parse();
   std::cout << input << std::endl;
   res->Print();
   delete res;

   std::cout << "OK" << std::endl;
}

void incorrect_test(const std::string & input) {
   std::cout << "Incorrect test: " + input + " ... ";
   Parser p;
   try {
      p.UpdateString(input);
      Tree * res = p.parse();
   } catch (std::exception &e) {
      std::cout << e.what() << std::endl;
   }
}

int main (void) {
   for (size_t i = 0; i < 100; i++) {
      test_size(100);
   }
   priority_test();

   std::cout << "======================== INCORRECT TEST ==================" << std::endl;
   incorrect_test("(a and b))");
   incorrect_test("an and b");
   incorrect_test("and and b");
   incorrect_test("a and");
   correct_test("not not a");

}