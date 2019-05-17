 <<<<<< formata 
 
 Este programa foi desenvolvido para a leitura de números sem formatação e sua conversão 
 para sua versão formatada e por extenso. As entradas devem ser fornecidas via arquivo e 
 saidas são também escritas para arquivo, em formato csv (ver Dependencias). 
 
 Os passos principais são: 
     1. Lê o arquivo de entrada, linha à linha; 
     2. Separa a parte inteira da parte decimal; 
     3. Quebra a parte inteira em partes de milhar. 
     4. Traduz cada uma das partes em sua forma por extenso. 
        4.1. Quebra os dígitos de centenas, dezenas e unidades. 
        4.2. Traduz cada um para a forma extensa, respeitando regras de lookahead. 
        4.3. Acrescenta sufixo de centavos, reais, milhares etc. 
     5. Concatena o valor original, a versão formatada e a forma extensa em uma linha .csv. 
     6. Excreve a linha csv no arquivo de saida. 
  
 @params: 
     [Sem parametros de linha de comando] 
  
 Dependencias: 
     - Arquivo de entrada "./entrada.txt", no diretório corrente. 
     - Acesso de escrita no diretório corrente para escrever "./saida.csv". 
 
