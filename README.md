

<div align="center">
  <img src="https://github.com/user-attachments/assets/87e9a69d-790a-4e16-a52c-0d686a06ad90" alt="Banner Controlador Gráfico" width="100%">
  <h1>Controlador Gráfico Embarcado: Integração HPS-FPGA</h1>
  <p>
    <strong>Sistema de Zoom em Tempo Real com Interface Mouse/Teclado na Placa DE1-SoC</strong>
  </p>
</div>

<br>

  <strong id="sobre">Sobre o Projeto 🔻</strong>
  <br>
    
  <details>
      <summary><strong>Definição do problema</strong></summary>
      <br>
      <p align="justify">&emsp;O projeto consiste no desenvolvimento de um sistema embarcado para redimensionamento de imagens em tempo real, simulando aplicações de vigilância. O objetivo é integrar um controlador gráfico implementado em FPGA a uma aplicação em linguagem C através de uma API (driver) personalizada, utilizando um repertório de instruções próprio. O sistema deve carregar imagens no formato BITMAP e permitir a interação do usuário via periféricos, utilizando o mouse para selecionar regiões de interesse (janelas) e o teclado para controlar os níveis de zoom in e zoom out (teclas + e -) na janela, com o resultado processado sendo renderizado via saída VGA sobre a imagem original.</p>

   <p> <a href="https://github.com/DestinyWolf/Problema-SD-2025-2"> Repositório do coprocessador original</a>, o qual usamos na FPGA. </p>

   </details>
<details>
   <summary><strong>Introdução</strong></summary>
  <br>
  <p align="justify">&emsp;O foco deste trabalho (Etapa 3) foi a criação da infraestrutura de software necessária para tornar o coprocessador FPGA interativo e mais completo, com o zoom em modo janela (picture in picture). Desenvolvemos módulos em C, os quais reconhecem os dispositivos de E/S, reconhecem os eventos de cada dispositivo (clicar com o botão direito do mouse, por exemplo), seleciona a janela através de uma interface em C que informa as coordenadas do mouse e aplica o Zoom in/out. Apesar de não haver quaisquer mudanças no código do coprocessador <a href="https://github.com/DestinyWolf/Problema-SD-2025-2">(link aqui)</a>, nosso projeto implementa uma série de algorítmos e funções que executam todas as ações propostas pelo problema.
Este read.me detalha a arquitetura da solução desta etapa do projeto. Desenvolvedores interessados em sistemas embarcados críticos encontrarão no link a seguir maiores detalhes sobre a implementação sólida e modular das etapas anteriores desse projeto.</p>

<a href="https://docs.kernel.org/input/index.html](https://github.com/vicss21-D/PBL-SD2">Etapa 2</a> <br>
<a href="https://github.com/DestinyWolf/Problema-SD-2025-2">Etapa 1</a> <br>

</details>
   <details>
     <summary><strong>Colaboradores</strong></summary>
     
   <table align="center">
      <tr>
        <td align="center">
          <a href="https://github.com/MisKaeya">
            <img src="https://github.com/user-attachments/assets/2c258244-f619-4859-bae2-96a1419f25d7" width="100px;" alt="Maria José"/><br>
            <sub><b>Maria José Neta</b></sub>
          </a>
        </td>
        <td align="center">
          <a href="https://github.com/GuiSantosHashDaSilva">
            <img src="https://github.com/user-attachments/assets/64be6d7b-1890-4647-9840-9cf8b80e3de3" width="100px;" alt="Guilherme Moreira"/><br>
            <sub><b>Guilherme Moreira</b></sub><br>
          </a>
        </td>
        <td align="center">
          <a href="https://github.com/vicss21-D">
            <img src="https://github.com/user-attachments/assets/c6dafd6c-eef0-4fae-a291-0354d5d355a8" width="100px;" alt="Adson Victor"/><br>
            <sub><b>Adson Victor Souza</b></sub><br>
          </a>
        </td>
      </tr>
    </table>
  </details>

  <details>
    <summary><strong>Referências</strong></summary>
    <a href="https://www.kernel.org/doc/Documentation/input/input.txt"> Linux Input drivers v1.0 </a> <br>
    <a href="https://docs.kernel.org/input/index.html"> Input Documentation</a> <br>
    <a href="https://stackoverflow.com/questions/16695432/input-event-structure-description-from-linux-input-h?noredirect=1&lq=1"> struct input_event structure (stack overflow)</a><br>
    <a href="https://www.arquivodecodigos.com.br/visualizar_dica.php?dica=2921-c-obtendo-as-coordenadas-do-mouse-durante-um-evento-mouseup-mousedown-mousemove-mousehover-ou-mouseclick.html">Obtendo as coordenadas do mouse durante um evento</a> <br>
    <a href="https://docs.kernel.org/input/index.html"> Input Documentation</a> <br>
    
  
  </details>
<hr>

