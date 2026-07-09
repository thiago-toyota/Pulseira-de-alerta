# Pulseira de Alerta

## Conceito do projeto

O projeto consiste em uma **pulseira de alerta com feedback háptico** para auxílio em locomoção urbana de pedestres e outros usuários vulneráveis da via (como ciclistas e motociclistas). Através do recebimento de um alerta de perigo do servidor (como veículos se aproximando ou desvios inesperados), a pulseira vibra em um padrão de duração e intensidade únicos, näo apenas notificando o usuário de que ele deve entrar em estado de alerta mas também fomentando maior memória cognitiva/associativa entre vibração e perigo. 

Apesar da **contribuição principal do projeto ser o dispositivo vestível**, a fim de testar o funcionamento da pulseira foi implementado um **servidor websocket** simples para o envio dos alertas. O projeto não é restrito a essa escolha de protocolo de comunicação: poderia ter sido feito em TCP por exemplo. O importante é o fluxo de informação, e não a tecnologia. Também, foi construído a pulseira inteligente utilizando componenetes eletrônicos e o reaproveitamento de algumas peças para se fazer a estrutura do vestível, bem como a implementação da **aplicação de alertas** no microcontrolador do dispositivo. 
  
## Pré-requisitos e recursos utilizados
Para a construção do circuito do vestível, utilizou-se o microcontrolador **ESP32 C3 Super Mini**, o módulo de vibração **Vibracall MV50**, o módulo carregador **TP4056** e uma **bateria LiPo** 3,7V de 500mAh. A soldagem foi feita com estanho utilizando fios Ethernet. 

Para a construção da estrutura da pulseira, utilizou-se uma fita velcro e uma carcaça de um sensor de movimento. 

Para a aplicação de alertas da pulseira, foi utilizado a linguagem C++/Arduino. Como bibliotecas, foi utilizado:
1. **WiFi.h**: para conectar o microcontrolador à rede/
2. **WebSocketsClient**: para estabelecer a conexão com o servidor. Faz parte da biblioteca WebSockets, de [Markus Sattler](https://www.arduinolibraries.info/libraries/web-sockets)

Para a aplicação do servidor, foi utilizado a linguagem Python. Como bibliotecas, foi utilizado:
1. **websockets**: para implementar o protocolo de comunicação do servidor, WebSocket.

Alguns links úteis que foram usados, principalmente em relação ao Arduino:
1. [**Tutorial de primeiros passos com o ESP32 C3**](https://randomnerdtutorials.com/getting-started-esp32-c3-super-mini/).
2. [**Repositório da biblioteca WebSocketsClient**](https://github.com/Links2004/arduinoWebSockets/tree/master).

Outra dica é, antes de "colocar a mão na massa", passar um bom tempo (talvez a maior parte do tempo) planejando e projetando. Algumas [aplicações Web](https://wokwi.com/projects/new/esp32-c3) simulam os circuitos, permitindo aprender o básico sobre microcontroladores, componentes (como módulos de vibração, LED), conexão WiFi, etc. A partir desse ponto, a evolução natural é comprar um kit breadboard, contendo o breadborad (uma placa de prototipação de circuitos) e jumper cables (fios que permitem facilmente fazer e desfazer conexões entre componentes na placa), além do microcontrolador e talvez alguns componentes básicos, como luzes LED. Um exemplo de site que reune todos esses componentes é o [UsinaInfo](https://www.usinainfo.com.br).
  
## Passo a passo
![Imagem](https://github.com/thiago-toyota/Pulseira-de-alerta/blob/main/Pulseira/Imagens/breadboard.jpeg)

Para dar início ao projeto, foi feito diversos projetos no [WokWi](https://wokwi.com/projects/new/esp32-c3). Quando estava seguro dos componenentes necessários e do mapa do circuito, foi feito a compra de tais eletrônicos e do kit breadboard. A imagem anterior demonstra o projeto do dispositivo: a bateria está soldada no módulo carregador através dos pinos B+ e B-. Tal módulo fornece carga para o esp32 (pino 3,3V e GND) e para o módulo de vibração (VCC e GND). O esp ainda se conecta ao módulo de vibração através do pino GPIO4 (que para o circuito final foi trocado pelo GPIO1).

Após essa primeira validação, as conexões foram efetivamente soldadas. A imagem a seguir mostra o resultado final

![Imagem](https://github.com/thiago-toyota/Pulseira-de-alerta/blob/main/Pulseira/Imagens/pulseira.png)

Da imagem:

(a). Estrutura da pulseira

(b). Microcontrolador Esp32 C3 Super Mini

(c). Módulo de vibração Vibracall MV50

(d). Módulo carregador TP4056

(e). Bateria LiPo 500mAh

A seguir, o esquema de conexões final:

| Origem | Destino |
|--------|---------|
| Bateria LiPo fio vermelho (+) | TP4056 B+ |
| Bateria LiPo fio preto (-) | TP4056 B- |
| TP4056 OUT+ | ESP32 3,3V |
| TP4056 OUT+ | MV50 VCC |
| TP4056 OUT- | ESP32 GND |
| TP4056 OUT- | MV50 GND |
| ESP32 GPIO1 | MV50 IN |

A partir desse ponto, foi feito as aplicações. O arquivo "alerta.ino" contém o código da aplicação Arduino de alertas, e o "websocket.py" o servidor. O arquivo "payload.json" possui um pacote que simula uma mensagem de risco que o servidor envia à aplicação.

## Instalação
É necessário instalar o Arduino Studio para rodar a aplicação "alerta.ino" no esp32. O [**tutorial de primeiros passos com o ESP32 C3**](https://randomnerdtutorials.com/getting-started-esp32-c3-super-mini/) auxilia bastante nessa parte. Recomendo fortemente seguir ele.

Também, para testar a aplicação, foi feito um servidor auxiliar WebSocket. Foi utilizado o [**Render**](https://render.com) para subir o servidor on-line. Ele funciona a partir de um repositório. Assim, é necessário criar um repositório (no GitHub ou similares) contendo os arquivos da pasta Servidor e então, conectar sua conta ao Render para que ele acesse seu repositório.

### Exemplos:
a)
  ```
  Execute o comando X Y Z, no terminal, na pasta do projeto
  ```
b)
  1. Abra a pasta 
  2. Execute o comando A B C no terminal
  3. Compile os arquivos X, Y e Z juntos
  4. Crie um arquivo W.txt de entrada

## Execução
Primeiro, vamos colocar no ar o servidor. Na plataforma do Render, adicione um novo serviço Web. Em "Build Command", coloque:
  ```
  pip install -r requirements.txt
  ```
E em "Start Command", coloque:
 ```
  py websocket.py
  ```
Após isso, clique em "Start Web Service". Agora o servidor está no ar.

Vamos pegar o URL que o Render gerou para o servidor. Vá para seu projeto (My Project, provavelmente) e no serviço que acabamos de criar. Abaixo do seu username do GitHub, aparecerá o URL. Copie tudo que vier APÓS "https://".

Com o Arduino Studio, abra o arquivo "alerta.ino". Troque "ssid" e "password" para as credenciais da sua rede WiFi e o "serverHost" para o que você copiou do Render.

Agora o que falta é apenas instalar a aplicação no esp32. Novamente, é recomendado seguir o [**tutorial de primeiros passos com o ESP32 C3**](https://randomnerdtutorials.com/getting-started-esp32-c3-super-mini/). 
Abaixo, dou uma explicação rápida da instalação

Clique em Tools > Board > Board Manager. Procure por **esp32**, e instale o "esp32 by Espressif Systems". 

Após a instalação, vá em Tools > USB CDC on Boot e ative-o. Vá em Tools > Upload Speed e escolha "115200".

Para mostrar o terminal e os "logs", vá em Tool > Serial Monitor. Em Serial Monitor, certifique-se de que a velocidade está em 115200 baud.

Após isso, conecte via usb o microcontrolador no computador e selecione a placa (esp32 c3) e a porta (entrada USB). Para instalar a aplicação, clique em "Upload". Se tudo der certo, o circuito vibrará por 2,5 segundos após o recebimento do pacote do servidor, como visto na figura abaixo.

![Imagem](https://github.com/thiago-toyota/Pulseira-de-alerta/blob/main/Pulseira/Imagens/funcionamento.png)

## Bugs/problemas conhecidos
Às vezes, após a instalação da aplicação no microcontrolador, nada aparece no serial monitor, indicando que a instalação não foi bem sucedida mesmo que, pelo terminal Output, nenhum problema ocorreu. Para resolver, aperte o botão RESET no ESP. A placa possui 2 botões, RESET e BOOT. O RESET fica localizado do lado dos pinos de alimentação (3,3V e GND).

## Autor
Thiago Massayuki Toyota - thiago.toyota@estudante.ufscar.br
