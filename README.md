# Projeto Final - Automação e Monitoramento Residencial

* <b>Descrição geral</b>:

 <div align="center">
   <img src="plantaBaixa.png" alt="planta" width="50%" height="20%"/></center>
</div>

   O sistema tem como objetivo uma pequena automação residencial. O sistema deve controlar alguns elementos dentro de um apartamento, como as cortinas, temperatura do ar condicionado, a tranca da porta, dimmer das luzes, etc. Também deve monitorar algumas variáveis, como a própria temperatura, a velocidade do vento do lado de fora, entre outros. O sistema é controlado através de um Arduino e um firmware escrito em C++. As variáveis de controle são alteradas e monitoradas via uma interface web desenvolvida usando HTML, CSS, Js e o framework Bootstrap. As informações são transmitidas ao controlador via um servidor web JavaScript. 

* <b>Comunicação</b>

  O projeto utiliza o protocolo de comunicação mestre-escravo Modbus em modo ASCII via RS-232 (Recommendad Standart-232), o que só permite dois dispositivos na rede, comumente conhecido como conexão ponto-a-ponto, sendo o Modbus o mestre, e o Arduino o escravo.
  
 <div align="center">
   <img src="figura1.png" alt="modbus" width="50%" height="20%"/></center>
</div>

  Utilizando o Modbus ASCII, cada unidade de 8 bits transmite como dois caracteres ASCII. O ASCII pode ter até um segundo entre os caracteres sem criar um erro na comunicação. Quando uma mensagem é enviada entre um mestre e o escravo, o código de função (function code) é o responsável em dizer para o escravo que tipo de ação ele deve fazer. No Modbus ASCII, o function code será 2 caracteres na messagem enviada.
 
 <div align="center">
    <img src="mensagemModbus.png" alt="mensagem" width="50%" height="20%"/></center>
 </div>
 
 -----ESQUEMÁTICO PDF-----------
 
 
