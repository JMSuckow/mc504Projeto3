MC504 - Projeto 3
=============

Integrante:

João Marcos Suckow Rodrigues   136253

Este projeto propunha ao aluno implementar um driver fictício simples que possuísse parâmetros controlados por ioctl. Além disto era necessário fazer uma aplicação que testasse o driver implementado.

Foi utilizado como base para a resolução deste trabalho a série [Linux Device Drivers](http://www.opensourceforu.com/tag/linux-device-drivers-series/)

Para a resolução foi escolhido a implementação de um cofre de dinheiro focado em pessoas que viajam com frequência para o exterior podendo, assim, armazenar diferentes tipos de moedas como euro, dólar e real. Entretanto, este não é um cofre qualquer. A fim de que o usuário possa interagir com ele é necessário passar por um driver.

A fim de facilitar esta interação foi desenvolvido um programa para intermediar a relação viajante-cofre. A seguir encontra-se os comandos para se utilizar quando for necessário mexer no cofre.

./app -u : Serve para destrancar (unlock) o cofre a fim de se usar as demais funcionalidades do mesmo. Será pedida a combinação do cofre.
./app -l : Serve para trancar (lock) o cofre para que outras pessoas não possam mexer nele.
./app -d : Serve para depositar certa quantia de dinheiro no cofre.
./app -w : Serve para sacar (withdraw) certa quantia de dinheiro do cofre.
./app -b : Serve para verificar o seu saldo (balance).
./app -h : Ajuda caso esqueça alguma destas funções.


