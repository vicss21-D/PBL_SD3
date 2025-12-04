

<div align="center">
  <img src="https://github.com/user-attachments/assets/87e9a69d-790a-4e16-a52c-0d686a06ad90" alt="Banner Controlador Gráfico" width="100%">
  <h1>Controlador Gráfico Embarcado: Integração HPS-FPGA</h1>
  <p>
    <strong>Sistema de Zoom em Tempo Real com Interface Mouse/Teclado na Placa DE1-SoC</strong>
  </p>
</div>

<br>

  <h1 id="sobre">Sobre o Projeto 🔻</h1>
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
  <p align="justify">&emsp;O foco deste trabalho (Etapa 3) foi a criação da infraestrutura de software necessária para tornar o coprocessador FPGA interativo e mais completo, com o zoom em modo janela (picture in picture). Desenvolvemos módulos em C, os quais reconhecem os dispositivos de E/S, reconhecem os eventos de cada dispositivo (clicar com o botão direito do mouse, por exemplo), seleciona a janela através de uma interface em C que informa as coordenadas do mouse e aplica o Zoom in/out. Para o desenvolvimento eficiente dessa etapa do projeto, foi utilizado um coprocessador já existente <a href="https://github.com/DestinyWolf/Problema-SD-2025-2">(link)</a>, mas aqui houveram alteraçoes no barramento de saida dos dados da imagem fpga-hps, e na forma que o tratamento do sinal selection memory é feito. Acesse nosso coprocessador alterado <a href="https://github.com/vicss21-D/PBL-SD2">aqui</a>
 .Nosso projeto implementa uma série de algorítmos e funções que executam todas as ações propostas pelo problema.
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
    <a href="https://abracloud.com.br/computacao-heterogenea-futuro-processamento-dados/"> Computação heterogênea</a> <br>
    <a href="https://www.bing.com/ck/a?!&&p=3211db47cb642146d7c9e5088d667dc052a50c31eef7d9b772b636cabf565ce8JmltdHM9MTc2NDcyMDAwMA&ptn=3&ver=2&hsh=4&fclid=0d258bc0-949a-6726-24bc-98a795bf66bd&psq=protocolo+AXI&u=a1aHR0cHM6Ly9kb2N1bWVudGF0aW9uLXNlcnZpY2UuYXJtLmNvbS9zdGF0aWMvNjhiMDNiZWIwMWFlOTUyZDk1NTlmOWVi"> Protocolo AXI <br>
    <a href="https://drive.google.com/file/d/1dBaSfXi4GcrSZ0JlzRh5iixaWmq0go2j/view?usp=sharing"> Manual do Kit de desenvolvimento DE1-SoC</a> <br>
  
  </details>

<h1 id="requisitos">Requisitos do Sistema 🔻</h1>
<br>
<details>
  <summary><strong>Hardware, Software e Dependências</strong></summary>
  <br>
  
  <h3>1. Hardware e Periféricos</h3>
  <p align="justify">&emsp;Este projeto foi desenvolvido especificamente para a plataforma Altera/Intel FPGA, utilizando o mapeamento de memória do HPS (Hard Processor System).</p>
  <ul>
    <li><strong>Kit de Desenvolvimento:</strong> Placa Terasic DE1-SoC (Cyclone V SoC).</li>
    <li><strong>Interface de Vídeo:</strong> Monitor com entrada VGA (para visualização da saída do processador gráfico).</li>
    <li><strong>Periféricos de Entrada:</strong> Teclado (no computador) e Mouse USB (conectado à porta USB do HPS na placa).</li>
    <li><strong>Conectividade:</strong> Cabo Ethernet ou Serial (UART) para acesso ao terminal Linux da placa.</li>
  </ul>

  <h3>2. Ambiente de Software (Host/Target)</h3>
  <p align="justify">&emsp;O software é projetado para ser compilado e executado nativamente no sistema operacional da placa (Linux Embarcado).</p>
  <ul>
    <li><strong>Sistema Operacional:</strong> Linux Embarcado (Kernel compatível com ARMv7).</li>
    <li><strong>Compilador C:</strong> GCC (GNU Compiler Collection) instalado no Linux da placa.</li>
    <li><strong>Assembler:</strong> GNU Assembler (as) para a montagem do driver <code>api.s</code>.</li>
    <li><strong>Utilitários:</strong> <code>make</code> (para automação da build) e bibliotecas padrão C (<code>glibc</code>, <code>math.h</code>).</li>
    <li><strong>Privilégios:</strong> Acesso <code>sudo</code> é obrigatório, pois o driver acessa diretamente o <code>/dev/mem</code> para controlar a ponte HPS-FPGA.</li>
  </ul>

  <h3>3. Dependências de Hardware (FPGA)</h3>
  <p align="justify">&emsp;O software (Driver e Aplicação) atua como controlador e depende que o hardware esteja presente. Sem o hardware carregado, a escrita nos endereços de memória causará travamento do sistema (Bus Error).</p>
  <ul>
    <li><strong>Bitstream (.sof/.rbf):</strong> A FPGA deve estar programada com o circuito do Processador Gráfico (desenvolvido na Etapa 1).</li>
  </ul>
</details>
  
  <details>
    <summary><strong>Detalhamento dos periféricos utilizados utilizados</strong></summary> <br>
    <h3>1. Mouse</h3>
<ul>
  <li><strong>Marca:</strong> Dell.</li>
  <li><strong>Modelo (M/N):</strong> M-UVDEL1.</li>
  <li><strong>Número da Peça (DP/N):</strong> 0C8639.</li>
  <li><strong>Número de Série (S/N):</strong> HCD53811343.</li>
  <li><strong>Especificações Elétricas:</strong> 5V (volts), 100mA (miliamperes).</li>
</ul>

<p align="justify">&emsp;Mouse óptico com fio (USB). É um modelo "clássico" de 2 botões + roda de rolagem (scroll wheel). O ano de distribuição desse modelo, M-UVDEL1 — é um periférico legacy, comum em desktops Dell (como as linhas Dimension e Optiplex) — foi aproximadamente entre 2004 e 2009. É um mouse padrão corporativo daquela época. O dispositivo possui várias aprovações regulatórias visíveis, como FCC (EUA), CE (Europa), VCCI (Japão) e UL (segurança), indicando que foi um produto vendido e aprovado globalmente.</p>

<div align="center">
  <img src="https://github.com/user-attachments/assets/3fc8602a-4533-4ec5-858f-6cba44493910" alt="Mouse Dell M-UVDEL1" width="30%">
  <br><sub>Figura: Mouse Dell utilizado no projeto</sub>
</div>

<p align="justify"><strong>Como foi reconhecido pela placa?</strong><br>
Através da função <code>mouse.utils</code>, que é mais detalhada <a href="#mouse_utils">aqui</a>.</p>

<br>

<h3>2. Teclado</h3>
<ul>
  <li><strong>Dispositivo:</strong> Teclado USB com fio (Wired Keyboard).</li>
  <li><strong>Marca:</strong> Lenovo.</li>
  <li><strong>Modelo:</strong> KU-1619.</li>
  <li><strong>Data de Fabricação (MFG):</strong> 26 de Novembro de 2020.</li>
  <li><strong>P/N (Part Number):</strong> SD50L79988.</li>
  <li><strong>FRU P/N:</strong> 00XH693.</li>
  <li><strong>Código de Barras:</strong> 8SSD50L79988AVLC0BT0989.</li>
  <li><strong>Alimentação:</strong> 5V, 100mA (padrão USB).</li>
  <li><strong>Conectividade:</strong> Cabo USB integrado.</li>
</ul>

<p align="justify">&emsp;O modelo KU-1619 é geralmente comercializado como "Lenovo Essential Wired Keyboard". É um teclado de membrana de perfil baixo, muito robusto e silencioso, frequentemente fornecido junto com desktops corporativos da linha ThinkCentre ou estações de trabalho. Fabricado no final de 2020, é uma unidade relativamente nova.</p>

<div align="center">
  <img src="https://github.com/user-attachments/assets/7ac693f9-5ab1-4b46-a441-f6cff93d6d94" alt="Teclado Lenovo KU-1619" width="30%">
  <br><sub>Figura: Teclado Lenovo utilizado para controle</sub> 

</div>

<p align="justify"><strong>Como foi reconhecido pela placa?</strong><br>
O algoritmo que descreve a leitura do teclado está na main.c, melhor explicado <a href="#main">aqui</a>. Embora a seleção da janela seja feita através do mouse conectado na placa, o teclado segue conectado no PC.</p>

<br>

<h3>3. Monitor</h3>
<ul>
  <li><strong>Produto:</strong> Monitor LED Widescreen.</li>
  <li><strong>Marca:</strong> Philips.</li>
  <li><strong>Modelo na Carcaça:</strong> 191EL.</li>
  <li><strong>Modelo Técnico (ID):</strong> 191EL2SB.</li>
  <li><strong>Número de Série:</strong> AF001143056440.</li>
  <li><strong>Data de Fabricação:</strong> Outubro de 2011.</li>
  <li><strong>Tecnologia:</strong> Monitor LCD com retroiluminação LED.</li>
  <li><strong>Alimentação:</strong> 12V DC, 3.0A.</li>
  <li><strong>Tamanho:</strong> 19”.</li>
</ul>

<div align="center">
  <img src="https://github.com/user-attachments/assets/c3b143a6-062c-4d45-a364-f24cdbfffedb" alt="Monitor Philips 191EL" width="30%"> 

  <br><sub>Figura: Monitor Philips utilizado para saída VGA</sub>
</div>

<p align="justify"><strong>Como foi reconhecido pela placa?</strong><br>
A saída VGA e a integração com a GPU são as responsáveis por essa implementação, especificamente no <code>vga_module.v</code>, o qual você pode visualizar <a href="https://github.com/vicss21-D/PBL_SD3/blob/main/FPGA/aux_files/vga_module.v">aqui</a>.</p>
    
  </details>

<br>

<h1 id="instalacao">Instalação e Execução 🔻</h1>
<br>
<details>
  <summary><strong>Guia Passo a Passo</strong></summary>
  <br>

  <h3>1. Requisitos Prévios</h3>
  <p align="justify">&emsp;Para a execução correta do projeto, certifique-se de que o ambiente atenda aos seguintes requisitos:</p>
  <ul>
    <li>Possuir conexão com a internet e ter a placa e o PC conectados na mesma rede (use o cabo de rede).</li>
    <li>Possuir o <strong>Git</strong> e o compilador <strong>GCC</strong> instalados.</li>
    <li>Utilizar uma placa de desenvolvimento <strong>DE1-SoC</strong>.</li>
    <li>Ter o coprocessador gráfico carregado na FPGA (<a href="https://github.com/vicss21-D/PBL-SD2">Link do Repositório</a>).</li>
    <li><strong>Monitor VGA:</strong> Para exibir o processamento de vídeo.</li>
    <li><strong>Mouse USB:</strong> Deve estar conectado à entrada USB da placa para interação.</li>
    <br>
    <div align="center">
      <img src="https://github.com/user-attachments/assets/dd4688db-df4d-4edd-bc38-48bac4c00fca" alt="Conexão VGA" width="30%">
      <br><sub>Exemplo de conexão VGA na placa</sub>
    </div>
    
  </ul>

  <h3>2. Instalação do Projeto</h3>
  <p align="justify">&emsp;Acesse o menu <em>Code</em> deste repositório e faça o download do arquivo <strong>.ZIP</strong>.</p>
  
  <div align="center">
    <img src="https://github.com/user-attachments/assets/99d5478a-e2be-4406-8c3c-b25dafe53adf" alt="Figura 1. Local de download" width="50%"> 
    <br><sub>Figura 1. Local exato de onde baixar o arquivo ZIP</sub>

  </div>
  <br>

  <p align="justify">&emsp;Crie uma pasta específica para o projeto e extraia os arquivos. <strong>Nota:</strong> Esta estrutura de pastas deve ser enviada para dentro do sistema de arquivos da placa (via <em>SFTP</em>).</p>

  <div align="center">
    <img src="https://github.com/user-attachments/assets/91857ab8-19d8-4030-ab0f-e0e8a63243b6" alt="Figura 2. Estrutura de arquivos" width="60%">
    <br><sub>Figura 2. A pasta do projeto deve conter estes elementos</sub> 
  <br>
    
  </div>
  
  <p align="center">
    <a href="https://github.com/vicss21-D/PBL-SD2#user-content-3-manuais-e-resultados">Como enviar meus arquivos dentro do sistema de arquivos da placa?</a>
  </p>

  <h3>3. Compilação e Execução</h3>
  
  <h4>No lado da FPGA (Hardware):</h4>
  <p align="justify">&emsp;Acesse a pasta <code>FPGA</code> e compile o código utilizando o <strong>Quartus II</strong>. O arquivo <code>soc_system.qpf</code> é a base do projeto e deve ser sintetizado para gerar o bitstream <code>.sof</code>.</p>
  <a href="#GuiaQuartus">Como compilar no quartus e colocar o código na placa?</a>
 
 <br> 

  <div align="center">
    <img src="https://github.com/user-attachments/assets/2dfaa1b7-9378-4006-8545-4eaab9f983c1" alt="Figura 3. Arquivo soc_system.qpf" width="60%"> 
    <br><sub>Figura 3. O arquivo soc_system.qpf aberto no Quartus</sub> 

  </div>

  <h4>No lado do HPS (Software):</h4>
  <p align="justify">&emsp;Acesse o terminal da placa (via Serial ou SSH). Navegue até a pasta onde os arquivos do HPS foram salvos. Como o driver manipula memória física, é necessário privilégio de superusuário:</p>
  <a href="https://github.com/vicss21-D/PBL-SD2#user-content-3-manuais-e-resultados">Como acessar a placa via terminal?</a>
  
  <pre>
  sudo su
  make run
  </pre>
  
  <p align="justify">&emsp;O comando <code>make run</code> irá compilar o código C e executar o programa automaticamente.</p>

</details> 

<details>
  <summary><strong id="mouse_utils">Navegando pela main. Fluxo de operação</strong></summary>
  <br>
  
  <p align="justify">&emsp;Aqui o usuário aprende como funciona a intrface em C.</p>
  
<h3>1. Inicialização e Execução</h3>
<p>
  Para iniciar o sistema, abra o terminal na pasta raiz do projeto. É necessário executar com privilégios de superusuário (<code>sudo</code>) para que o driver possa mapear a memória da FPGA e acessar os eventos do mouse.
</p>
<pre><code>sudo make run</code></pre>
 <p>
  O sistema fará o <em>boot</em> automático: detectará o driver do mouse (ex: <code>/dev/input/event2</code>), inicializará a ponte HPS-FPGA e resetará o hardware.
</p>

<div align="center">
  <img src="https://github.com/user-attachments/assets/010771fb-e591-4a8b-8306-db56a35f620a" alt="Tela de Boot e Detecção de Mouse" width="600px"> 

  <p><em>Figura 1: Sequência de boot e detecção automática do mouse.</em></p>
</div>

<h3>2. O Painel de Controle (Dashboard)</h3>
<p>
  Ao iniciar, você verá o Menu Principal. Preste atenção na <strong>Barra de Status</strong> no topo da tela. Ela é o seu guia principal:
</p>
<ul>
  <li><strong>Buffer C:</strong> Mostra se a imagem já está na memória RAM do Linux.</li>
  <li><strong>FPGA VRAM:</strong> Mostra se a imagem já foi enviada para o hardware.</li>
  <li><strong>Zoom Level:</strong> Monitora o nível atual de zoom (0 = Original).</li>
</ul>

<div align="center">
  <img src="https://github.com/user-attachments/assets/aef08e21-fe24-4285-86d3-d8648a112eb3" alt="Menu Principal Vazio" width="600px"> 


  <p><em>Figura 2: Menu Principal mostrando o estado inicial do sistema.</em></p>
</div>

<h3>3. Carregando Dados (Workflow Básico)</h3>
<p>
  Antes de processar, você precisa de uma imagem. Selecione a <strong>Opção 1</strong> para carregar um arquivo BMP ou a <strong>Opção 2</strong> para gerar um gradiente de teste.
</p>
<p>
  Após carregar, a Barra de Status mudará de <code>[VAZIA]</code> para <code>[CARREGADA]</code>.
</p>

<div align="center">
  <img src="https://github.com/user-attachments/assets/6eb12e9e-2a5a-4a13-987e-801377adc635" alt="Carregando Imagem" width="600px">
  <p><em>Figura 3: Processo de carga de imagem e atualização de status.</em></p>
</div>

<h3>4. Funcionalidade Avançada: Zoom Regional Interativo</h3>
<p>
  Para utilizar o zoom seletivo com mouse, selecione a <strong>Opção 8</strong>. O sistema entrará no modo interativo:
</p>

<h4>Passo A: Seleção de Área</h4>
<p>
  Mova o mouse físico. As coordenadas X/Y aparecerão no terminal em tempo real.
</p>
<ul>
  <li><strong>Botão Esquerdo:</strong> Define o primeiro canto do retângulo (Início).</li>
  <li><strong>Botão Direito:</strong> Define o segundo canto (Fim) e confirma a seleção.</li>
</ul>

<div align="center">
  <img src="https://github.com/user-attachments/assets/7f6155fd-2199-4559-981b-ae0337478345" alt="Captura de Coordenadas" width="600px"> 

  <p><em>Figura 4: Interface de captura de área mostrando as coordenadas em tempo real.</em></p>
</div>

<h4>Passo B: Navegação e Cache simulada</h4>
<p>
  Após selecionar a área, o sistema exibe o menu de navegação. Observe o indicador de <strong>Cache</strong> (ex: <code>[*0* _ _]</code>), que mostra quais níveis já foram processados.
</p>
<ul>
  <li>Pressione <strong><code>+</code></strong> para aplicar Zoom In (Processar na FPGA).</li>
  <li>Pressione <strong><code>-</code></strong> para aplicar Zoom Out (Recuperar do Cache instantaneamente).</li>
  <li>Pressione <strong><code>0</code></strong> para sair e restaurar a imagem original.</li>
</ul>

<div align="center">
  <img src="https://github.com/user-attachments/assets/d4935308-df49-41f9-b10f-394e0873ef9b" alt="Menu de Navegação Regional" width="600px">  

  <p><em>Figura 5: Sub-menu de navegação com status do cache visualizado.</em></p>
</div>
</details>

<br>

<h1 id="softwares">Softwares e Tecnologias Utilizados 🔻</h1>
<br>
<details>
  <summary><strong>Ferramentas de Desenvolvimento</strong></summary>
  <br>
  
  <p align="justify">&emsp;Abaixo estão listadas as principais tecnologias empregadas no desenvolvimento desta solução, abrangendo desde a descrição de hardware até a interface de usuário.</p>

  <h3>Linguagem Verilog</h3>
  <p align="justify">&emsp;Linguagem de descrição de hardware (HDL) criada em 1993. Foi utilizada para projetar e simular os sistemas digitais na FPGA. Sua sintaxe, similar à linguagem C, permite uma descrição concisa do comportamento dos circuitos integrados.</p>

  <h3>Linguagem C</h3>
  <p align="justify">&emsp;Vinda dos anos 70, a linguagem C foi escolhida por sua portabilidade, eficiência e controle de baixo nível. Ela é a base para a produção da interface de usuário e para a comunicação direta com os módulos de hardware (driver).</p>

  <h3>Assembly ARMv7</h3>
  <p align="justify">&emsp;Utilizada para controlar os circuitos da arquitetura ARMv7 (CPUs de 32 bits). Esta linguagem permite escrever instruções legíveis para humanos que seguem o princípio RISC (computação com conjunto reduzido de instruções), possibilitando execuções otimizadas e manipulação precisa dos registradores.</p>

  <h3>Quartus Prime</h3>
  <p align="justify">&emsp;Software oficial da Intel/Altera para desenvolvimento, compilação e planejamento da FPGA. Foi utilizado para sintetizar o hardware e carregar os códigos que descrevem o comportamento físico da placa.</p>

  <h3>Visual Studio Code (VS Code)</h3>
  <p align="justify">&emsp;Editor de texto avançado criado pela Microsoft. Foi o ambiente principal de desenvolvimento, oferecendo suporte a depuração, destaque de sintaxe e extensões que facilitam a escrita de códigos em C e Python.</p>

  <h3>Compilador GNU (GCC)</h3>
  <p align="justify">&emsp;O <em>GNU Compiler Collection</em> é um conjunto de compiladores de código aberto. Foi utilizado para compilar o código C para a arquitetura ARM do HPS, garantindo a otimização do código de máquina gerado.</p>

  <h3>Nano</h3>
  <p align="justify">&emsp;Editor de texto em linha de comando presente no Linux embarcado do kit DE1-SoC (versão 2.2.6). Foi utilizado para edições rápidas de scripts e ajustes no código diretamente na placa, oferecendo uma interface leve e intuitiva.</p>

</details>
<details>
  <summary><strong>Visão Geral da placa</strong></summary>
  <br>

  <h3>1. Visão Geral da Placa</h3>
  <p align="justify">&emsp;O kit de desenvolvimento <strong><a href="https://drive.google.com/file/d/1dBaSfXi4GcrSZ0JlzRh5iixaWmq0go2j/view?usp=sharing">DE1-SoC</a></strong>, ilustrado na Figura 4, baseia-se na arquitetura <em>System-on-Chip</em> (SoC) do Intel® Cyclone® V. Este dispositivo integra, em um único chip, um <strong>Hard Processor System (HPS)</strong> e uma <strong>FPGA (Field Programmable Gate Arrays)</strong>.</p>
  
  <p align="justify">&emsp;A placa conta com recursos robustos como memória DDR3, conexões USB e Ethernet, além de diversos periféricos, conferindo-lhe alta flexibilidade para múltiplas aplicações. A interação com o sistema operacional Linux embarcado é realizada via computador host utilizando o protocolo <strong>SSH (Secure Shell)</strong>, assegurando uma comunicação criptografada e eficiente.</p>

  <div align="center">
    <img src="https://github.com/user-attachments/assets/de1f754e-cd3c-4c9b-88d0-3f9380310e52" alt="Figura 4. Placa DE1-SoC" width="50%">
    <br><sub>Figura 4. Placa utilizada para o projeto (Fonte: FPGAcademy)</sub> 

  </div>

  <h3>2. Sistema Computacional da Placa</h3>
  <p align="justify">&emsp;O diagrama de blocos ilustrado na Figura 5 detalha a arquitetura interna e as interconexões do chip Intel® Cyclone® V. A estrutura do sistema divide-se claramente entre o HPS e a FPGA:</p>
  
  <ul>
    <li><strong>HPS (Hard Processor System):</strong> É constituído por um processador dual-core ARM® Cortex-A9 MPCore™, memória DDR3 dedicada e periféricos. Ele executa uma distribuição Linux responsável pelo gerenciamento de alto nível e tarefas de propósito geral (software).</li>
    <li><strong>FPGA:</strong> Oferece a versatilidade necessária para criar hardware customizado via blocos lógicos programáveis, onde reside o nosso controlador gráfico.</li>
  </ul>

  <div align="center">
    <img src="https://github.com/user-attachments/assets/9223a9a9-d834-45ee-937f-578f0d781695" alt="Figura 5. Diagrama HPS vs FPGA" width="60%"> 
    <br><sub>Figura 5. Diagrama dos componentes da arquitetura Cyclone V</sub>
  </div>
  <br>

  <h3>Integração via Pontes (Bridges)</h3>
  <p align="justify">&emsp;A integração entre esses dois domínios ocorre de forma bidirecional através das chamadas <strong>FPGA Bridges</strong>. No fluxo do HPS para a FPGA, o processador consegue acessar todos os dispositivos de Entrada/Saída (E/S) conectados à lógica programável utilizando a técnica de <strong>mapeamento de memória</strong>. Os detalhes específicos sobre o endereçamento desses periféricos podem ser consultados na documentação técnica da placa.</p>

  <div align="center">
    <img src="https://github.com/user-attachments/assets/bfe88c75-bd44-499b-b82f-8380cdf3f1aa" alt="Figura: Representação Lúdica" width="60%"> 
    <br><sub>Figura 6. Representação visual da comunicação e endereçamento</sub>
  </div>

</details>
<h1 id="processador">Menu Arquitetura🔻</h1>
<br>

<div align="center">
  <img src="https://github.com/user-attachments/assets/3c82ce77-960a-49ad-b84b-8d78be2e56f7" alt="Diagrama geral do projeto" width="70%"> 

  <br><sub>Figura: Diagrama geral do projeto</sub>
</div>
  
  <h3>Visão Geral</h3>
  <p align="justify">&emsp;O projeto adota uma arquitetura de Co-design Hardware/Software, tirando proveito da estrutura do SoC (System on Chip) da placa DE1-SoC. O sistema é dividido em duas camadas principais que se comunicam através de uma ponte de barramento de alta velocidade (Lightweight HPS-to-FPGA AXI Bridge). As camadas são HPS (códigos em C e assembly) e FPGA (códigos em verilog). Nessa etapa do projeto, falaremos mais sobre o HPS, para maiores detalhes da FPGA (códigos do hardware), <a href="https://github.com/vicss21-D/PBL_SD3/tree/main/FPGA">acesse esse read.me aqui</a>.</p>

  

  <h3>Arquitetura em Camadas</h3>
  <p align="justify">&emsp;A solução foi estruturada para garantir modularidade e abstração de hardware:</p>
  <ul>
    <li><strong>Camada de Aplicação (C):</strong> É o "cérebro" de alto nível. Responsável por ler arquivos do sistema de arquivos do Linux (Bitmaps) chamando as funções do assembly, gerenciar a interface com o usuário (Teclado/Mouse) e a leitura e reconhecimento dos dispositivos de E/S.</li>
    <li><strong>Camada de Driver (Assembly):</strong> É o "tradutor". Atua como uma API que abstrai a complexidade do hardware. Ela converte chamadas de função (como ASM_Store ou PixelReplication) em operações de escrita e leitura em endereços físicos de memória mapeados.</li>
    <li><strong>Camada de Hardware (FPGA):</strong> É o "músculo". Um circuito digital customizado que possui sua própria memória de vídeo (VRAM) e é composto pelas instruções em verilog. Aqui estão os ajustes de clock, PIO’s e memória, <a href="https://github.com/DestinyWolf/Problema-SD-2025-2">entenda mais aqui</a>.</li>
  </ul>
  
<details>
  <summary><strong>Como Funciona?</strong></summary>
  <p align="justify">&emsp;A arquitetura do sistema fundamenta-se no paradigma de <strong>Computação Heterogênea</strong> <a href="https://abracloud.com.br/computacao-heterogenea-futuro-processamento-dados/">(veja mais sobre aqui)</a> em um <em>System-on-Chip</em> (SoC), onde o fluxo de controle é particionado entre um processador de propósito geral (ARM Cortex-A9) e um núcleo de propriedade intelectual (IP Core) customizado na FPGA. A implementação do Zoom Regional opera através de um mecanismo de <strong>Co-design Hardware/Software</strong> que otimiza o <em>trade-off</em> entre latência de processamento e uso de memória.</p>

  <h3>Fluxo de Zoom In (Hardware e Comunicação)</h3>
 <p align="justify">&emsp;No domínio do software (Host), o gerenciamento de contexto utiliza uma estrutura de dados do tipo <strong>Pilha (LIFO - Last In, First Out)</strong> alocada na SDRAM para preservar os estados de buffer anteriores. Durante a operação de Zoom In, o sistema processa a imagem completa, extraindo e salvando no buffer apenas os pixels correspondentes à Região de Interesse (ROI). Em seguida, transfere esses dados através da ponte <strong>Lightweight HPS-to-FPGA. <a href="https://www.bing.com/ck/a?!&&p=3211db47cb642146d7c9e5088d667dc052a50c31eef7d9b772b636cabf565ce8JmltdHM9MTc2NDcyMDAwMA&ptn=3&ver=2&hsh=4&fclid=0d258bc0-949a-6726-24bc-98a795bf66bd&psq=protocolo+AXI&u=a1aHR0cHM6Ly9kb2N1bWVudGF0aW9uLXNlcnZpY2UuYXJtLmNvbS9zdGF0aWMvNjhiMDNiZWIwMWFlOTUyZDk1NTlmOWVi">AXI</a></strong>, utilizando mapeamento de I/O (MMIO) sobre controladores PIO (Parallel I/O). Esse algoritmo SIMULA uma cache.</p>

<p align="justify">&emsp;A comunicação ocorre de forma síncrona e sequencial, onde o processador escreve os dados pixel a pixel diretamente no barramento, sem o uso de acesso direto à memória (DMA). O hardware dedicado recebe esse fluxo de dados e aplica o algoritmo de <strong>Nearest Neighbor</strong> (Vizinho Mais Próximo) ponto a ponto, armazenando o resultado na memória interna enquanto o processador aguarda a finalização em estado de <em>polling</em> nos registradores de status.</p>
  <h3>Fluxo de Zoom Out (Recuperação e Overlay)</h3>
  <p align="justify">&emsp;Em contrapartida, a operação de Zoom Out elimina a necessidade de recálculo aritmético reverso (que degradaria a qualidade do sinal devido a perdas de amostragem) adotando uma abordagem de <strong>Recuperação de Estado</strong>. O processador executa um <em>pop</em> na pilha de buffers, restaurando os dados armazenados na memória principal.</p>

  <p align="justify">&emsp;A composição final da imagem utiliza uma técnica de <strong>Overlay por Software</strong>, onde o frame buffer é manipulado através de operações de <em>Read-Modify-Write</em>: o background original é restaurado e a janela processada (ou recuperada) é escrita nas coordenadas de destino, garantindo integridade visual sem a necessidade de um controlador de vídeo com suporte nativo a camadas de hardware (hardware layers).</p>

  <div align="center">
    <img src="https://github.com/user-attachments/assets/04e349ab-7020-49cc-ade7-a932a07867c9" alt="Figura. Fluxo de dados" width="70%"> 
    <br><sub>Figura. Diagrama do funcionamento geral</sub>
  </div>
   <div align="center">
    <img src="https://github.com/user-attachments/assets/ae6be45b-c3a8-4ee9-bdcf-21ff6ccabcfb" alt="Figura. Fluxo de dados" width="70%"> 
    <br><sub>Figura. Funcionando!</sub> 

  </div>
</details>

<details>
  <br>
  
  <div align="center">
  <img src="https://github.com/user-attachments/assets/17ae857a-1705-41ce-98bb-1a2531e141f3" width="70%" />
    
  <br><sub>Figura: Diagrama da arquitetura C </sub>
  </div>
  <summary><strong>Aquitetura do C</strong></summary>
      <p>
    O código atua como uma aplicação de console em <strong>Linux (User Space)</strong> que gerencia o fluxo de dados de imagem. Ele não processa a imagem matematicamente (tarefa delegada à FPGA), mas atua como um orquestrador de estado e memória.
  </p>
  
  <h4>1. Estruturas de Dados Principais</h4>
  <p>
    A estrutura central do sistema é a <code>RegionalZoomContext</code>. Ela eleva o código de um simples despachante para um gerenciador de estado robusto.
  </p>
  <ul>
    <li><strong><code>RegionalZoomContext</code>:</strong>
      <ul>
        <li>Armazena coordenadas da janela (<code>x, y, width, height</code>).</li>
        <li>Mantém um <strong>Cache de Software</strong> (<code>zoom_buffers[]</code>): Uma pilha de arrays que guarda o resultado de cada nível de zoom, evitando reprocessamento em navegações "in/out".</li>
        <li>Guarda o <strong>Background</strong> (<code>original_full_image</code>): Cópia da imagem original, essencial para restaurar o fundo ao mover a janela de zoom.</li>
      </ul>
    </li>
  </ul>
  
  <h4>2. Manipulação de Arquivos e Memória (BMP)</h4>
  <p> Implementação de um parser manual (<code>load_bmp</code>) sem dependências externas:</p>
  <ul>
    <li><strong>Leitura Binária:</strong> Processa os cabeçalhos <code>BMPHeader</code> e <code>BMPInfoHeader</code> byte a byte.</li>
    <li><strong>Conversão de Cores:</strong> Converte RGB para Grayscale usando a fórmula de luminância: <code>(299*R + 587*G + 114*B) / 1000</code>.</li>
    <li><strong>Alinhamento:</strong> Trata o <em>padding</em> de 4 bytes típico de arquivos BMP para evitar distorções na memória.</li>
  </ul>
  
  <h4>3. Camada de Abstração de Hardware (HAL Simulada)</h4>
  <p>Encapsula chamadas de baixo nível em funções C de alto nível:</p>
  <ul>
    <li><code>send_image_to_fpga</code>: Itera sobre o array de pixels e chama <code>ASM_Store</code>, incluindo contagem de erros de escrita.</li>
    <li><code>read_fpga_window</code>: Lê uma região da memória do dispositivo, selecionando automaticamente o banco de memória (<code>mem_sel</code>) baseado no contexto.</li>
    <li><code>execute_algorithm</code>: Implementa o padrão de <strong>Polling</strong>:
      <ol>
        <li>Dispara o hardware.</li>
        <li>Aguarda a flag <code>ASM_Get_Flag_Done</code> em loop.</li>
        <li>Aplica um <em>Timeout</em> de segurança.</li>
      </ol>
    </li>
  </ul>
  
  <h4>4. Lógica do "Zoom Regional"</h4>
  <p>A função <code>regional_zoom_apply</code> atua como uma máquina de estados para o sistema de janelas:</p>
  <ol>
    <li><strong>Verificação de Cache:</strong> Checa se o nível de zoom existe em <code>zoom_buffers</code>.</li>
    <li><strong>Cache Hit:</strong> Recupera dados da RAM instantaneamente (Zero processamento).</li>
    <li><strong>Cache Miss:</strong>
      <ul>
        <li>Salva estado atual.</li>
        <li>Envia para FPGA processar.</li>
        <li>Realiza <em>Read Back</em> da região processada.</li>
        <li>Atualiza o Cache.</li>
      </ul>
    </li>
    <li><strong>Overlay:</strong> Restaura o background original e sobrescreve apenas a janela de zoom, criando a interface gráfica.</li>
  </ol>
  
  <h4>5. Interação com Mouse (Linux Input Subsystem)</h4>
  <p>Acesso direto aos arquivos de dispositivo (<code>/dev/input/event*</code>) via <code>find_and_open_mouse</code>:</p>
  <ul>
    <li>Lê estruturas <code>input_event</code> cruas (low-level).</li>
    <li>Filtra <code>EV_REL</code> para calcular coordenadas virtuais X/Y.</li>
    <li>Filtra <code>EV_KEY</code> para detectar cliques.</li>
  </ul>
  
  <h4>6. Loop Principal (Main)</h4>
  <p>Um loop infinito clássico de sistemas embarcados:</p>
  <ul>
    <li><strong>Renderiza Menu:</strong> Interface de console.</li>
    <li><strong>Input Blocking:</strong> Aguarda comando do usuário.</li>
    <li><strong>Dispatcher:</strong> Switch/Case roteando funções.</li>
    <li><strong>Gestão de Flags:</strong> Protege o sistema contra estados inválidos (ex: checando <code>Min_Zoom</code>/<code>Max_Zoom</code>).</li>
  </ul>
  
  <hr>
  
  <blockquote>
    <p><strong>Resumo Técnico:</strong> O código C atua como um <strong>Gerenciador de Fluxo e Memória</strong> que prepara dados (BMP &#8594; Array), orquestra o tempo de execução (Trigger &#8594; Wait &#8594; Read), gerencia a visualização (Overlay) e trata exceções do sistema.</p>
  </blockquote>
  
  <div align="center">
    <img src="https://github.com/user-attachments/assets/9ab50ed8-e8fe-4440-97d5-dd39f734f204" alt="Figura. Fluxo de dados" width="50%">
    <br><sub>Figura. Fluxo de dados geral</sub>
  </div>

</details>

<details>
  <br>
  
  <div align="center">
  <img src="https://github.com/user-attachments/assets/0ca887fd-970f-42bc-b811-3483e2ca2691" width="70%" /> 

    
  <br><sub>Figura: Diagrama da arquitetura Assembly </sub>
  </div>
  <summary><strong>Aquitetura do Assembly</strong></summary>
    <p>
  A biblioteca <code>api.s</code> implementa uma arquitetura de <strong>Driver de Dispositivo em Espaço de Usuário (User-Space Device Driver)</strong> baseada em MMIO. O design prioriza a eficiência do barramento e a organização lógica do código.
</p>

<h4>1. Encapsulamento e Visibilidade (Public vs. Private)</h4>
<p>
  A arquitetura do driver organiza o código em dois níveis de visibilidade para garantir modularidade e manutenção (DRY - <em>Don't Repeat Yourself</em>):
</p>
<ul>
  <li><strong>Funções Públicas (Visíveis ao C):</strong> São os pontos de entrada globais (<code>.global</code>) invocados pela aplicação principal (ex: <code>ASM_Store</code>, <code>API_initialize</code>). Elas validam parâmetros e gerenciam o fluxo de alto nível.</li>
  <li><strong>Funções Privadas (Invisíveis ao C):</strong> Rotinas internas (ex: <code>_pulse_enable_safe</code>, <code>_ASM_Set_Instruction</code>) que não são exportadas para o linker. Elas encapsulam a lógica repetitiva de manipulação de registradores e bitwise, reduzindo a duplicação de código.</li>
</ul>

<h4>2. Protocolo de Instrução Unificado (29-bit Packet)</h4>
<p>
  Para maximizar a eficiência e evitar múltiplas escritas no barramento para uma única operação, a arquitetura utiliza um <strong>Pacote de Instrução Unificado</strong>. Todas as informações necessárias para configurar o hardware são compactadas em um único registrador de 32 bits (utilizando 29 bits efetivos):
</p>
<ul>
  <li><strong>[Bits 28..21] O Quê (8 bits):</strong> O valor do pixel (Payload) a ser escrito (em operações de escrita).</li>
  <li><strong>[Bit 20] Onde - Banco (1 bit):</strong> Seleção do banco de memória alvo (Principal ou Secundária).</li>
  <li><strong>[Bits 19..3] Onde - Endereço (17 bits):</strong> O endereço linear da memória de vídeo.</li>
  <li><strong>[Bits 2..0] O Que Fazer (3 bits):</strong> O <em>Opcode</em> da operação (ex: Store, Load, Algoritmos).</li>
</ul>

<h4>3. Canais de Retorno e Controle Dedicados</h4>
<p>
  Enquanto o envio de comandos é unificado, o retorno de dados e o controle de fluxo utilizam canais de I/O dedicados (PIOs) para simplificar o hardware:
</p>
<ul>
  <li><strong>Canal de Leitura de Dados (8 bits):</strong> Um PIO exclusivo (<code>PIO_DATAOUT</code>) dedicado a receber o valor do pixel retornado pela FPGA durante operações de leitura (LOAD).</li>
  <li><strong>Interface de Status (4 bits):</strong> Um canal paralelo para leitura das Flags de estado do hardware (Done, Error, Max/Min Zoom).</li>
  <li><strong>Sinal de Controle (1 bit):</strong> Um sinal de <em>Enable</em> simples utilizado exclusivamente para disparar (trigger) o início do processamento configurado no pacote de instrução.</li>
</ul>

<hr>

<blockquote>
  <p><strong>Resumo do Fluxo:</strong> O processador monta e envia um "pacote completo" (Ordem + Endereço + Dados) em um ciclo, pulsa o <em>Enable</em>, e aguarda o resultado ou status através dos canais dedicados de retorno.</p>
</blockquote>

</details>

<details>
  <br>
    <div align="center">
  <img src="https://github.com/user-attachments/assets/9f7a6a27-a91d-4ca5-b496-e6e6f30ad62b" width="50%" /> 
    
  <br><sub>Figura: Diagrama da do verilog </sub>
  </div>
  <summary><strong>Arquitetura do Verilog</strong></summary>
  <p>
   O sistema é classificado como uma <strong>Arquitetura de Acelerador Dedicado com Memória Compartilhada e Gerenciamento de Vídeo Integrado</strong>. O design segue o modelo <em>Control-Datapath</em>, com uma especialização crítica no gerenciamento de endereçamento.
  </p>

<h4>1. Plano de Controle (UC - Unidade de Controle)</h4>
<p>O "cérebro" do sistema, implementado como uma Máquina de Estados Finitos (FSM).</p>
<ul>
  <li><strong>Função:</strong> Orquestra a sincronização de todos os módulos. A UC não processa pixels; ela gerencia sinais de controle.</li>
  <li><strong>Interface:</strong> Recebe o <code>INSTRUCTION</code> (Opcode) do processador Host e dispara sinais de escrita (<code>WrEn</code>), seleção de Muxes e modos de operação.</li>
  <li><strong>Feedback:</strong> Monitora e exporta flags de status (<code>Done</code>, <code>Error</code>, <code>Max/Min Zoom</code>) para o módulo <code>PIO FLAGS</code>.</li>
</ul>

<h4>2. Unidade de Controle de Endereçamento (ACU)</h4>
<p>Um diferencial arquitetural que remove a complexidade de cálculo de endereços da FSM principal.</p>
<ul>
  <li><strong>Arquitetura:</strong> Gerador de Endereços Programável.</li>
  <li><strong>Função:</strong> Abstrai a navegação na memória. Para algoritmos como Zoom, onde o acesso não é linear, a ACU traduz comandos de alto nível (<code>Step</code>, <code>Op</code>) em endereços físicos de leitura e escrita simultâneos para as memórias.</li>
</ul>

<h4>3. Hierarquia de Memória (Arquitetura Tri-Buffer)</h4>
<p>O sistema utiliza três bancos de memória distintos para segregar responsabilidades:</p>
<ul>
  <li><strong>Mem A (Input/Work Buffer):</strong> Armazenamento primário da imagem a ser processada e fonte principal de dados para a unidade de execução.</li>
  <li><strong>Mem C (Swap/Intermediate Buffer):</strong> Armazena resultados temporários, permitindo operações complexas que não podem ser feitas <em>in-place</em>.</li>
  <li><strong>Mem B (Video RAM / Framebuffer):</strong> Possui arquitetura de acesso duplo implícita. Uma porta de escrita controlada pelo sistema e uma porta de leitura contínua dedicada exclusivamente ao <strong>VGA Controller</strong>, isolando o domínio de vídeo do processamento (evitando <em>screen tearing</em> ou <em>flicker</em>).</li>
</ul>

<h4>4. Unidade de Execução de Algoritmos (UAE)</h4>
<p>O núcleo aritmético (ALU especializada) do acelerador.</p>
<ul>
  <li><strong>Fluxo de Dados:</strong> Recebe um pixel bruto da Memória A, aplica a lógica combinacional do filtro selecionado (ex: Nearest Neighbor) baseado no sinal <code>OP UAE</code>, e entrega o pixel transformado para a Memória C.</li>
  <li><strong>Desacoplamento:</strong> A UAE processa fluxos de dados sem conhecimento de endereços, delegando a localização espacial para a ACU.</li>
</ul>

<h4>5. Subsistema de Vídeo (VGA)</h4>
<p>Opera paralelamente ao processamento:</p>
<ul>
  <li><strong>VGA Controller:</strong> Gera sinais de sincronismo (HSync/VSync) e coordenadas de varredura (<code>Next_x</code>, <code>Next_y</code>).</li>
  <li><strong>Acesso Direto:</strong> Lê diretamente da <code>Mem B</code> para converter dados digitais em sinais de cor (<code>Color_out</code>) para o DAC.</li>
</ul>

<h4>6. Interface de I/O (Memory Mapped)</h4>
<p>A comunicação com o Host (CPU) é feita via sinais digitais diretos (PIO):</p>
<ul>
  <li><strong>Entrada:</strong> Sinais como <code>ADDR MEM</code> e <code>INSTRUCTION</code> configuram o sistema.</li>
  <li><strong>Multiplexação de Saída:</strong> Um conjunto de Muxes (Multiplexadores) permite que a CPU leia resultados tanto da Memória C quanto da Memória A, ou roteie dados entre as memórias internas.</li>
</ul>

<hr>

<blockquote>
  <p><strong>Resumo do Pipeline:</strong> A arquitetura funciona em estágios: <strong>(1) Configuração</strong> (Carga de dados na Mem A/B), <strong>(2) Processamento</strong> (UC comanda ACU+UAE movendo dados de A &#8594; C) e <strong>(3) Write-Back/Display</strong> (Dados processados movem-se de C &#8594; B para vídeo ou leitura da CPU).</p>
</blockquote>
</details>

<br>
<h1 id="algoritmos">Detalhamento dos novos algoritmos🔻</h1>
<br>

<details>
  <summary><strong id="mouse_utils">Módulos do C: Mouse_utils.c</strong></summary>
  <br>
  
  <p align="justify">&emsp;Este módulo em C é responsável por detectar, inicializar e interpretar dados brutos vindos de um dispositivo de mouse no Linux. Ele abstrai a complexidade de ler arquivos de dispositivo e converte eventos de hardware em coordenadas de cursor utilizáveis.</p>

  <h3>Visão Geral</h3>
  <p align="justify">&emsp;O código opera em três etapas principais:</p>
  <ul>
    <li><strong>Verificação:</strong> Determina se um arquivo de dispositivo é realmente um mouse.</li>
    <li><strong>Descoberta:</strong> Varre o diretório <code>/dev/input</code> para encontrar um mouse conectado.</li>
    <li><strong>Processamento:</strong> Lê pacotes de dados do kernel, atualiza a posição do cursor e limita as coordenadas à resolução da tela (320x240).</li>
  </ul>

  <h3>Detalhamento das Funções</h3>

  <h4>1. Identificação de Hardware: <code>is_mouse</code></h4>
  <p align="justify">&emsp;Esta função atua como um filtro. No Linux, teclados, mouses e joysticks vivem na mesma pasta. Para saber quem é quem, perguntamos ao dispositivo quais "habilidades" (capabilities) ele possui.</p>
  <ul>
    <li><strong>Mecanismo:</strong> Usa a syscall <code>ioctl</code> com <code>EVIOCGBIT</code> para obter mapas de bits das funcionalidades.</li>
    <li><strong>Critério de Aprovação:</strong> O dispositivo é considerado um mouse se possuir:
      <ul>
        <li><code>REL_X</code>: Capacidade de movimento relativo no eixo horizontal.</li>
        <li><code>BTN_LEFT</code>: Capacidade de clicar com o botão esquerdo.</li>
      </ul>
    </li>
  </ul>

  <h4>2. Varredura e Conexão: <code>find_and_open_mouse</code></h4>
  <p align="justify">&emsp;Esta função automatiza a busca pelo periférico, evitando que o usuário precise saber qual arquivo (ex: <code>/dev/input/event3</code>) corresponde ao mouse.</p>
  <ul>
    <li><strong>Varredura:</strong> Utiliza <code>scandir</code> para listar todos os arquivos em <code>/dev/input/</code>.</li>
    <li><strong>Filtragem:</strong> Analisa apenas arquivos que começam com o prefixo "event".</li>
    <li><strong>Teste:</strong> Abre cada arquivo candidato e aplica a função <code>is_mouse</code>.</li>
    <li><strong>Retorno:</strong> Se encontrar, retorna o descritor de arquivo (fd) aberto e preenche os buffers com o caminho e nome. Se falhar, retorna -1.</li>
  </ul>

  <h4>3. Leitura de Dados: <code>read_and_process_mouse_event</code></h4>
  <p align="justify">&emsp;Esta é a função "coração" do módulo, chamada repetidamente (loop principal) para capturar ações do usuário.</p>
  <ul>
    <li><strong>Leitura Bruta:</strong> Lê uma estrutura <code>struct input_event</code> do kernel. Esta estrutura contém tipo (movimento ou botão), código (qual eixo ou qual botão) e valor.</li>
    <li><strong>Lógica de Movimento Relativo (EV_REL):</strong> Mouses enviam "o quanto andou" (delta), não "onde está". A função soma esse delta à posição atual do cursor (<code>current_cursor->x += ev.value</code>).</li>
    <li><strong>Clamping (Limitação de Borda):</strong> O código força o cursor a permanecer dentro dos limites 320x240. (x é travado entre 0 e 319, y é travado entre 0 e 239).</li>
  </ul>

  <h3>Estruturas de Dados Importantes</h3>
  <p align="justify">&emsp;Embora definidas nos headers do sistema (<code>linux/input.h</code>), é crucial entender o que está sendo manipulado:</p>
  <div align="center">
    <table border="1">
      <thead>
        <tr>
          <th>Estrutura</th>
          <th>Descrição</th>
        </tr>
      </thead>
      <tbody>
        <tr>
          <td><code>struct input_event</code></td>
          <td>Pacote padrão do Linux contendo type (ex: Movimento), code (ex: Eixo X) e value (ex: +10 pixels).</td>
        </tr>
        <tr>
          <td><code>Cursor</code></td>
          <td>Estrutura definida pelo usuário (em mouse_utils.h) que mantém o estado absoluto (X, Y) na tela.</td>
        </tr>
        <tr>
          <td><code>MouseEvent</code></td>
          <td>Estrutura simplificada para entregar ao programa principal apenas o que interessa.</td>
        </tr>
      </tbody>
    </table>
  </div>
  <br>

  <h3>Por que usar este código?</h3>
  <ul>
    <li><strong>Independência de Interface Gráfica:</strong> Este código funciona diretamente no terminal ou em sistemas embarcados sem servidor gráfico (como X11 ou Wayland).</li>
    <li><strong>Controle Absoluto:</strong> Permite implementar interfaces gráficas customizadas de baixo nível (ex: desenhar um cursor pixel a pixel em um Framebuffer).</li>
    <li><strong>Plug-and-Play:</strong> A função de descoberta automática permite conectar o mouse em qualquer porta USB sem precisar reconfigurar o software.</li>
  </ul>
</details>

<details>
  <summary><strong id="main">Módulos do C: Main.c</strong></summary>
  <br>

  <p align="justify">&emsp;Este é o arquivo fonte central do projeto (Host Application). Ele atua como orquestrador do sistema, gerenciando a interação com o usuário, o ciclo de vida das imagens, a comunicação com o hardware FPGA e o processamento de eventos de entrada (Teclado e Mouse).</p>

  <h3>Visão Geral</h3>
  <p align="justify">&emsp;O código implementa uma Interface de Linha de Comando (CLI) interativa que opera em um loop infinito. Diferente de scripts simples, este programa mantém o estado do sistema (níveis de zoom, buffers de imagem, descritores de arquivos) e coordena a execução de algoritmos acelerados por hardware.</p>

  <h3>Estruturas de Dados Críticas</h3>
  <p align="justify">&emsp;A inovação deste módulo está na estrutura de contexto para o zoom regional, que permite o funcionamento do sistema de "Desfazer/Undo".</p>
  
  <h4>RegionalZoomContext</h4>
  <p align="justify">&emsp;Esta struct atua como o descritor da janela de zoom.</p>
  
  <pre lang="c">
typedef struct {
    int x, y;           // Coordenadas do canto superior esquerdo da janela
    int width, height;  // Dimensões da janela
    int zoom_level;     // Nível atual (0 a 3)
    
    // A MÁGICA DO ZOOM OUT:
    // Uma pilha de ponteiros para armazenar os pixels de cada estágio.
    uint8_t *zoom_buffers[MAX_REGIONAL_ZOOM_LEVELS]; 
    int buffer_sizes[MAX_REGIONAL_ZOOM_LEVELS];
} RegionalZoomContext;</pre>

  <p align="justify">&emsp;<strong>Função:</strong> Mantém o histórico visual da região selecionada. Cada vez que um Zoom In é feito, a imagem anterior é salva em <code>zoom_buffers</code>. No Zoom Out, o buffer é recuperado.</p>

  <h3>Detalhamento das Funcionalidades</h3>

  <h4>1. Sistema de Zoom Regional (Picture-in-Picture)</h4>
  <p align="justify">&emsp;Esta é a lógica mais complexa do arquivo, implementada na função <code>regional_zoom_apply</code>. Ela gerencia o fluxo híbrido Hardware/Software.</p>
  <ul>
    <li><strong>Zoom In (+):</strong>
      <ul>
        <li><strong>Backup:</strong> Aloca memória na RAM e salva o estado visual atual da janela na pilha <code>zoom_buffers</code>.</li>
        <li><strong>Envio:</strong> Transfere a região atual para a memória da FPGA.</li>
        <li><strong>Processamento:</strong> Aciona o hardware (NearestNeighbor).</li>
        <li><strong>Leitura:</strong> Lê o resultado processado da FPGA.</li>
        <li><strong>Overlay:</strong> Restaura o fundo original e desenha a nova janela processada por cima.</li>
      </ul>
    </li>
    <li><strong>Zoom Out (-):</strong>
      <ul>
        <li><strong>Recuperação:</strong> Não aciona a FPGA para cálculo. Em vez disso, retira (pop) a imagem salva no nível anterior da pilha.</li>
        <li><strong>Restauração:</strong> Reescreve esses pixels na memória de vídeo, revertendo o zoom instantaneamente sem perda de qualidade.</li>
      </ul>
    </li>
  </ul>

  <h4>2. Tratamento de Entrada (Input Handling)</h4>
  <p align="justify">&emsp;O código lida com dois tipos de entrada de forma robusta:</p>
  <ul>
    <li><strong>Mouse (<code>capture_mouse_area</code>):</strong>
      <ul>
        <li>Utiliza o módulo <code>mouse_utils</code> para ler eventos brutos <code>/dev/input/event*</code>.</li>
        <li>Implementa uma máquina de estados simples: Esperando Canto 1 &rarr; Esperando Canto 2 &rarr; Área Capturada.</li>
        <li>Exibe coordenadas em tempo real no terminal.</li>
      </ul>
    </li>
    <li><strong>Teclado (<code>read_key_direct</code>):</strong>
      <ul>
        <li>Altera os atributos do terminal (termios) temporariamente para desabilitar o modo canônico e o eco.</li>
        <li>Isso permite capturar teclas (como +, -, ESC) instantaneamente sem que o usuário precise pressionar Enter, criando uma experiência de jogo/interativa.</li>
      </ul>
    </li>
  </ul>

  <h4>3. Integração com a API (FPGA Wrapper)</h4>
  <p align="justify">&emsp;O código envolve as chamadas de baixo nível da <code>api.h</code> com lógica de segurança e timeout:</p>
  <ul>
    <li><strong><code>send_image_to_fpga</code>:</strong> Itera sobre 76.800 pixels chamando <code>ASM_Store</code>. Inclui verificação de erros para abortar a transferência se o hardware não responder.</li>
    <li><strong><code>execute_algorithm</code>:</strong> Envolve o disparo do algoritmo com um loop de Polling (espera ativa). Se a flag DONE não subir dentro de TIMEOUT_LOOPS, o software aborta para evitar travamento do sistema.</li>
    <li><strong><code>read_fpga_window</code>:</strong> Uma função de diagnóstico crucial que permite ler uma área retangular arbitrária da VRAM para verificar se o zoom funcionou corretamente.</li>
  </ul>

  <h4>4. Carregamento de Imagens (BMP Parser)</h4>
  <p align="justify">&emsp;A função <code>load_bmp</code> implementa um decodificador manual de arquivos BMP:</p>
  <ul>
    <li>Valida a assinatura "BM" (0x4D42).</li>
    <li>Suporta múltiplas profundidades de cor (32, 24 e 8 bits).</li>
    <li>Realiza a conversão matricial de RGB para Escala de Cinza (Y = 0.299R + 0.587G + 0.114B) antes de armazenar no buffer.</li>
    <li>Trata a inversão vertical típica do formato BMP (que armazena linhas de baixo para cima).</li>
  </ul>

  <h3>Fluxo de Execução (Main Loop)</h3>
  <p align="justify">&emsp;O <code>main()</code> inicializa o sistema na seguinte ordem:</p>
  <ul>
    <li><strong>Hardware:</strong> <code>API_initialize()</code> (mmap) e <code>ASM_Reset()</code> (limpeza de registradores).</li>
    <li><strong>Periférico:</strong> <code>find_and_open_mouse()</code> (busca automática no /dev/input).</li>
    <li><strong>Loop de Eventos:</strong> Exibe o menu e aguarda comando.</li>
  </ul>
  <p align="justify">&emsp;O menu oferece 3 modos de operação distintos:</p>
  <ul>
    <li><strong>Modo de Carga:</strong> Carregar BMP ou gerar gradiente de teste.</li>
    <li><strong>Modo Global (Legado):</strong> Aplica zoom na tela inteira (opções 4-7).</li>
    <li><strong>Modo Regional (Interativo):</strong> Opção 9. Entra em um sub-loop onde o usuário usa o mouse para desenhar a janela e o teclado para controlar o zoom em tempo real.</li>
  </ul>

  <h3>Tratamento de Erros e Segurança</h3>
  <ul>
    <li><strong>Timeout:</strong> Impede loops infinitos se a FPGA travar.</li>
    <li><strong>Limites de Memória:</strong> Verifica se a janela do mouse está dentro dos limites 320x240 para evitar Segmentation Fault.</li>
    <li><strong>Limites de Zoom:</strong> Impede Zoom In além do nível 3 (estouro de buffer) e Zoom Out abaixo do nível 0.</li>
    <li><strong>Limpeza (Cleanup):</strong> Garante que <code>free()</code> seja chamado para os buffers de imagem e <code>API_close()</code> seja executado ao sair, liberando os recursos do sistema operacional.</li>
  </ul>

</details>

<br>
<h1 id="testes">Testes 🔻</h1>
<br>

<details>
  <summary><strong>Metodologia de Validação</strong></summary>
  <br>

  <h3>1. Teste de Loopback (Validação de Memória)</h3>
  <p align="justify">&emsp;Antes de tentar processar qualquer imagem, o código sugere que o primeiro teste foi garantir que o HPS conseguia escrever e ler da FPGA sem corromper dados.</p>
  <ul>
    <li><strong>Evidência:</strong> A função <code>read_fpga_window</code> e a opção 3 do menu ("Ler janela da FPGA... e exibir matriz").</li>
    <li><strong>O Teste:</strong>
      <ul>
        <li>O software escreve valores na VRAM (<code>ASM_Store</code>).</li>
        <li>O software lê os mesmos endereços de volta (<code>ASM_Load</code>).</li>
        <li>A função <code>print_matrix</code> exibe os números no terminal.</li>
      </ul>
    </li>
    <li><strong>Dedução:</strong> Se os números impressos no terminal correspondem ao que foi enviado, o barramento AXI, o Driver PIO e a Memória da FPGA estão funcionando. Se voltasse tudo 0 ou 0xFF, haveria um erro elétrico ou de mapeamento.</li>
  </ul>

  <h3>2. "Sanity Check" Visual (Padrão de Teste)</h3>
  <p align="justify">&emsp;Carregar um arquivo BMP é complexo (pode ter erro de header, leitura de arquivo, etc.). Para isolar problemas, o código inclui um gerador interno.</p>
  <ul>
    <li><strong>Evidência:</strong> A função <code>generate_test_pattern</code> (Opção 2 do menu).</li>
    <li><strong>O Teste:</strong>
      <ul>
        <li>Gerar um gradiente matemático (0 a 255) na RAM.</li>
        <li>Enviar para a FPGA.</li>
      </ul>
    </li>
    <li><strong>Dedução:</strong> Se o monitor VGA exibir um degradê suave de preto para branco, o sistema de vídeo está perfeito. Se exibir ruído ou faixas verticais, há erro na temporização do VGA ou na escrita da VRAM. Isso elimina a variável "Arquivo BMP corrompido" da equação.</li>
  </ul>

  

  <h3>3. Teste de Driver e Latência (Polling & Timeout)</h3>
  <p align="justify">&emsp;O código contém mecanismos de defesa contra travamentos, indicando que testes de estresse foram realizados.</p>
  <ul>
    <li><strong>Evidência:</strong> As constantes <code>TIMEOUT_LOOPS</code> e os loops <code>while(ASM_Get_Flag_Done() == 0)</code>.</li>
    <li><strong>O Teste:</strong>
      <ul>
        <li>Disparar um comando para a FPGA.</li>
        <li>O software conta o tempo.</li>
      </ul>
    </li>
    <li><strong>Dedução:</strong> Se o hardware travar (não levantar a flag DONE), o software não congela eternamente; ele aborta e avisa o usuário. Isso sugere que durante o desenvolvimento do Verilog, o hardware provavelmente travou várias vezes, forçando a implementação desse timeout no C.</li>
  </ul>

  <h3>4. Teste de Periférico Isolado (Mouse)</h3>
  <p align="justify">&emsp;O arquivo <code>mouse_utils.c</code> é quase um programa autônomo. A estrutura dele sugere que foi testado separadamente antes de ser integrado ao menu.</p>
  <ul>
    <li><strong>Evidência:</strong> Os printf detalhados dentro de <code>capture_mouse_area</code> ("CursorXY: ...").</li>
    <li><strong>O Teste:</strong>
      <ul>
        <li>Rodar o programa e mover o mouse.</li>
        <li>Verificar se as coordenadas no terminal param exatamente em 319 (X) e 239 (Y).</li>
      </ul>
    </li>
    <li><strong>Dedução:</strong> O desenvolvedor moveu o mouse fisicamente até os cantos da tela para garantir que a lógica de "clamping" (limites da tela) estava funcionando antes de tentar usar essas coordenadas para dar zoom.</li>
  </ul>

  <h3>5. Validação Algorítmica (Zoom In/Out)</h3>
  <p align="justify">&emsp;A validação final foi visual e funcional, testando a lógica de estados.</p>
  <ul>
    <li><strong>Evidência:</strong> O sistema de menus permite executar passos isolados (Carregar -> Zoom In -> Zoom In).</li>
    <li><strong>O Teste:</strong>
      <ul>
        <li>Carregar imagem.</li>
        <li>Aplicar Zoom In.</li>
        <li>Verificar visualmente se a imagem ficou "pixelada" (Nearest Neighbor funciona).</li>
        <li>Aplicar Zoom Out.</li>
        <li>Verificar se a imagem voltou ao original (teste da Pilha de Buffers).</li>
      </ul>
    </li>
    <li><strong>Dedução:</strong> O uso da Opção 9 ("Zoom Regional") foi o teste de integração final, validando se o recorte da memória (software) coincidia com a área que o usuário via na tela.</li>
  </ul>
  
</details>

<details>
  <summary><strong>Problemas encontrados (e corrigidos)</strong></summary>
<br>
<p>
Durante o desenvolvimento e testes de integração Hardware/Software, dois problemas principais foram identificados e mitigados:
</p>

<h4>1. Bloqueio de Execução no <code>wait_for_enter()</code></h4>
<ul>
  <li><strong> O Problema:</strong> O programa pausava inesperadamente ou exigia que o usuário pressionasse "Enter" duas vezes para prosseguir após certas operações.</li>
  <li><strong> Causa Técnica:</strong> A função <code>wait_for_enter()</code> chamava internamente <code>clear_input_buffer()</code>. Como o buffer já havia sido limpo após o <code>scanf</code> anterior (consumindo inclusive o <code>\n</code>), o comando <code>getchar()</code> subsequente ficava aguardando uma <em>nova</em> entrada de dados que não era necessária, travando o fluxo.</li>
  <li><strong> Solução:</strong> Refatoração da função <code>wait_for_enter()</code>. A chamada redundante de limpeza foi removida, assumindo que o buffer é gerido corretamente logo após as leituras de input no loop principal.</li>
</ul>

<div align="center">
  <img src="https://github.com/user-attachments/assets/e3e04e63-13c3-4940-b1e5-d2fd3426e99b"  alt="Trecho do erro">
  <br><sub>Figura: Trecho do erro</sub>   
</div>

<br>

<div align="center">
  <img src="https://github.com/user-attachments/assets/af924470-375e-434f-aac5-189441b808db"  alt="Trecho do erro">

  <br><sub>Figura: Trecho corrigido</sub> 
</div>


<h4>2. Instabilidade de Pixels em Requisições Rápidas (Zoom Burst)</h4>
<ul>
  <li><strong> O Problema:</strong> Ao pressionar a tecla de Zoom In (<code>+</code>) repetidamente em um curto intervalo de tempo, a imagem resultante na FPGA apresentava falhas de escrita ou pixels corrompidos.</li>
  <li><strong> Causa Técnica:</strong> O barramento de comunicação com a VRAM da FPGA não utiliza <em>pipelining</em> para o fluxo de comandos de zoom. O envio de múltiplos comandos consecutivos ("spamming" de teclas) causava uma condição de corrida (<em>race condition</em>), onde uma nova operação de leitura/escrita interrompia a anterior antes de sua conclusão.</li>
  <li><strong> Solução:</strong> Restrição operacional no fluxo de uso. O sistema requer que o usuário aguarde a conclusão visual do processamento (renderização do frame) antes de solicitar o próximo nível de zoom, garantindo a integridade dos dados na memória.</li>
</ul>
  <div align="center">
  <img src="https://github.com/user-attachments/assets/2d8c0104-fc2d-4957-8d5b-72c05366a0a5"  alt="Trecho do erro"> 

  <br><sub>Gif: Bug do zoom no monitor</sub> 
</div>

  <div align="center"> 

  <img src="https://github.com/user-attachments/assets/c85cbbe9-ddfd-49ec-a65f-c397002b4372"  alt="Trecho do erro"> 

  <br><sub>Gif: Zoom peformando da meneira ideal</sub> 
</div>

</details>
<br>
<h1 id="howto">Menu How to 🔻</h1>
<br>

<details>
  <summary><strong>Guia de Operação e Uso</strong></summary>
  <br>

  <h3>Como copiar os arquivos na placa</h3>
  <p align="justify">&emsp;Essa etapa é muito mais fácil do que parece! Você precisará copiar a sua pasta, e na opção “Outros locais” do seu gerenciador de arquivos, você colocará o endereço da placa.</p>
  
  <p align="center"><strong>Comando:</strong> <code>ssh://(IP da sua placa)</code></p>
  
  <p align="justify">&emsp;Tendo acessado o local da placa, cole a sua pasta lá!</p>


  <h3 id="GuiaQuartus">Como compilar e rodar na placa?</h3>
  
  <h4>Passo 01: Compilação</h4>
  <p align="justify">&emsp;Abra o arquivo <code>soc_system.qpf</code> no Quartus II, clique em <strong>“Start Compilation”</strong> e aguarde a compilação terminar.</p>
  <div align="center">
    <img src="https://github.com/user-attachments/assets/8917c2ea-8ee0-44b2-9fa2-7fc765f6d08e" alt="Acesso ao Quartus Programmer" width="70%">
    <br><sub>Página principal do Quartus</sub>
  </div> 
  
  <h4>Passo 02: Acessar o Programador</h4>
  <p align="justify">&emsp;Após compilado, abra o menu <strong>Programmer</strong> (Tools > Programmer).</p>
  
  <div align="center">
    <img src="https://github.com/user-attachments/assets/f2663426-99f8-4fda-beb2-36049b5b8727" alt="Acesso ao Quartus Programmer" width="70%"> 
    <br><sub>Interface do Programmer configurada</sub>
  </div>


  <h4>Passo 03: Detecção e Configuração</h4>
  <p align="justify">&emsp;Selecione a placa na opção <strong>Auto Detect</strong>, depois marque a opção <strong>Program/Configure</strong>. Se a opção não estiver disponível, clique em “Add File” e selecione o arquivo <code>.sof</code> gerado na pasta output_files.</p>
  <div align="center">
    <img src="https://github.com/user-attachments/assets/671b1279-4758-4518-b7db-3df75c8774d3" alt="Acesso ao Quartus Programmer" width="70%"> 
    <br><sub>Interface do Programmer configurada</sub>
  </div>
  
  <h4>Passo 04: Upload</h4>
  <p align="justify">&emsp;Pressione <strong>Start</strong>. Quando a barra de progresso atingir 100%, o coprocessador estará na placa!</p>


