#include <iostream>
#include <fstream>
#include <iostream>
#include <math.h>

/* Documentação do programa. */ 
void manual(){
   std::cout << " \
<<<<<< formata \n \
\n \
Este programa foi desenvolvido para a leitura de números sem formatação e sua conversão \n \
para sua versão formatada e por extenso. As entradas devem ser fornecidas via arquivo e \n \
saidas são também escritas para arquivo, em formato csv (ver Dependencias). \n \
\n \
Os passos principais são: \n \
    1. Lê o arquivo de entrada, linha à linha; \n \
    2. Separa a parte inteira da parte decimal; \n \
    3. Quebra a parte inteira em partes de milhar. \n \
    4. Traduz cada uma das partes em sua forma por extenso. \n \
       4.1. Quebra os dígitos de centenas, dezenas e unidades. \n \
       4.2. Traduz cada um para a forma extensa, respeitando regras de lookahead. \n \
       4.3. Acrescenta sufixo de centavos, reais, milhares etc. \n \
    5. Concatena o valor original, a versão formatada e a forma extensa em uma linha .csv. \n \
    6. Excreve a linha csv no arquivo de saida. \n \
 \n \
@params: \n \
    [Sem parametros de linha de comando] \n \
 \n \
Dependencias: \n \
    - Arquivo de entrada \"./entrada.txt\", no diretório corrente. \n \
    - Acesso de escrita no diretório corrente para escrever \"./saida.csv\". \n \
\n"; 
}

/*
 Função responsável pela traduação de algarismos, até centenas, em sua forma extensa.
 @params:
   int number: Algorismo em [0-9].
   int level: 1 para unidades, 10 para dezendas e 100 para centenas.  
   int lookahead: Usado quando os dígitos seguintes influenciam na forma extensa. 
                  Varia entre [0-9]. 
*/
std::string numeros2extenso(int number, int level, int lookahead) {
   switch (number * level + lookahead){
      case 1: return "um"; break;
      case 2: return "dois"; break;
      case 3: return "tres"; break;
      case 4: return "quatro"; break;
      case 5: return "cinco"; break;
      case 6: return "seis"; break;
      case 7: return "sete"; break;
      case 8: return "oito"; break;
      case 9: return "nove"; break;
      case 10: return "dez"; break;
      case 11: return "onze"; break;
      case 12: return "doze"; break;
      case 13: return "treze"; break;
      case 14: return "quatorze"; break;
      case 15: return "quinze"; break;
      case 16: return "dezeseis"; break;
      case 17: return "dezessete"; break;
      case 18: return "dezoito"; break;
      case 19: return "dezenove"; break;
      case 20: return "vinte"; break;
      case 30: return "trinta"; break;
      case 40: return "quarenta"; break;
      case 50: return "cinquenta"; break;
      case 60: return "sessenta"; break;
      case 70: return "setenta"; break;
      case 80: return "oitenta"; break;
      case 90: return "noventa"; break;
      case 100: return "cem"; break;
      case 101: return "cento"; break;
      case 200: return "duzentos"; break;
      case 300: return "trezentos"; break;
      case 400: return "quatrocentos"; break;
      case 500: return "quinhentos"; break;
      case 600: return "seissentos"; break;
      case 700: return "setecentos"; break;
      case 800: return "oitocentos"; break;
      case 900: return "novecentos"; break;
   }
   return "";
}

/*
 Função responsável pela determinação dos milhares em sua forma extensa.
 @params:
   int level: Varia entre [-1-5], atribuidos a nomenclaturas entre centavos e quadrilhões.  
   int texto: Usado para regularizar plural quando o valor é um.. 
*/
std::string traduzMilhares(int level, std::string texto){

  if (texto == "" || texto == " " || texto == "  ")
     return "";

  if (texto == "um" || texto == " um" || texto == "  um")
     level += 10;

  switch (level) {
     case -1: return " centavos"; break;
     case 9: return " centavo"; break;
     case 0: return " reais"; break;
     case 10: return " real"; break;
     case 1: return " mil"; break;
     case 11: return " mil"; break;
     case 2: return " milhões"; break;
     case 12: return " milhão"; break;
     case 3: return " bilhões"; break;
     case 13: return " bilhão"; break;
     case 4: return " trilhões"; break;
     case 14: return " trilhão"; break;
     case 5: return " quadrilhões"; break;
     case 15: return " quadrilhão"; break;
  }
  return "";
}

/*
 Traduz os tokens de milhares em sua representação completa por extenso. Função usada como
 wrapper das outras: numeros2extenso e traduzMilhares.
 @params:
   std::string milhar: tokens como "001", "230" e "000", obtidos da quebra do número original.  
   int level: ordem do token no número original. 
*/
std::string emExtenso(std::string milhar, int level) {
   int n = std::atoi(milhar.c_str());

   //std::cout << "DEBUG* Milhar convertido em inteiro: " << n << ".\n";

   int centenas = n / 100;
   int dezenas = ( n % 100) / 10;
   int unidades = ( n % 100) % 10;

   //std::cout << "DEBUG* Centenas=" << centenas << "; dezenas=" << dezenas << "; unidades=" << unidades <<".\n";
   int ahead =  ((centenas == 1) && (dezenas + unidades) > 0)? 1: 0;
   std::string extenso = numeros2extenso(centenas, 100, ahead);

   ahead = (dezenas != 1)? 0: unidades;
   std::string tmp = numeros2extenso(dezenas, 10, ahead);
   if (extenso == "" )
      extenso = tmp;
   else
      extenso += (tmp.length() > 0)?
         " e " + tmp:
         "";
   
   int flag = (ahead > 0)? 0: 1; 
   tmp = numeros2extenso(unidades * flag, 1, 0);
   if (extenso == "" )
      extenso = tmp;
   else
      extenso += (tmp.length() > 0)?
         " e " + tmp:
         "";

   return extenso + traduzMilhares(level, extenso);
}


/* Função principal. Ver manual.*/
int main(int argc, char **argv) {

   if (argc > 1) {
      manual();
      return 0;
   }

   std::string infilepath = "./entrada.txt";
   std::string outfilepath = "./saida.csv";
   std::ifstream file(infilepath);
   std::ofstream out(outfilepath);

   out << "Original,Formatado,Por Extenso\n";

   std::string original; 
   std::string ninteiro, ncomplementar;

   int linha = 0;
   while (std::getline(file, original)) {
      //std::cout << "+++++++++++++++++++++++++++++" << "\n";
      std::cout << "Processando linha #" << ++linha <<".\n";

      //---------------------------------------------------------
      // Separando parte inteira da parte decimal
      //---------------------------------------------------------

      // Caso o numero apresente tanto parcela inteira como decimal
      if(original.length() > 2 ) {
         ninteiro = original.substr(0, (original.length()-2));
         ncomplementar = original.substr((original.length()-2), 2);
      // se apenas a parte decimal foi providenciada
      } else {
         ninteiro = "0";
         // caso a parte decimal possua apenas um dígito, acrescentar zero a esquerda 
         ncomplementar = (original.length() > 1)? original: "0" + original;
      }

      //std::cout << "DEBUG* " << original << "\n";
      //std::cout << "DEBUG* " << ninteiro << "," << ncomplementar << "\n";


      //---------------------------------------------------------
      // Quebrando parte inteira em unidades de milhares
      //---------------------------------------------------------
      int i = 0;
      int l = ceil(ninteiro.length() / 3);
      int n = ninteiro.length() % 3;

      if (n == 0){
          n = 3; l--;
      } 


      //---------------------------------------------------------
      // Iterando sobre os tokens
      //---------------------------------------------------------
      std::string formatado = "R$ ";
      std::string porExtenso = "";
      while( i < ninteiro.length()) {
          std::string part = ninteiro.substr(i, n);
          std::string part_extenso = emExtenso(part, (l--));

          formatado += (i==0)? 
             part: 
             "." + part;

          if (part_extenso != ""){
             porExtenso += (i==0)?
                part_extenso:
                ", " + part_extenso;
          }

          //std::cout << "DEBUG* " << part << "\n";
          //std::cout << "DEBUG* " << part_extenso << "\n";
          i += n;
          n = 3;
      }

      //---------------------------------------------------------
      // Acrescentando centavos...
      //---------------------------------------------------------
      formatado += "," + ncomplementar;
      
      std::string centavos = emExtenso(ncomplementar, -1);
      if (porExtenso == "") {
         porExtenso = centavos;
      } else {
         porExtenso += (centavos != "")? " e " + centavos : "";
      }

      //std::cout << "DEBUG* " << formatado << "\n";
      //std::cout << "DEBUG* " << porExtenso << "\n";

      //---------------------------------------------------------
      // Compondo a saida e escrevendo em arquivo.
      //---------------------------------------------------------
      std::string lineout = original + ",\"" + formatado + "\",\"" + porExtenso + "\"\n";
      //std::cout << "DEBUG* " << lineout << "\n";

      out << lineout;
   }
   out.close();

   return 0;
}
