
# Sistema de Monitoramento com ESP32

Este repositório contém o código e a interface web de um sistema de monitoramento utilizando **ESP32**, sensores de temperatura e umidade, e uma interface web para visualização dos dados em tempo real.

## 📦 Descrição do Projeto

O projeto consiste em:

- 📡 Coleta de dados de sensores conectados ao ESP32.
- 🌐 Exibição dos dados via uma interface web (`index.html`) hospedada pelo próprio ESP32.
- 📊 Monitoramento em tempo real dos valores dos sensores.

## 🛠️ Tecnologias Utilizadas

- **ESP32**: microcontrolador com conectividade Wi-Fi.
- **Sensor DHT22**: para medição de temperatura e umidade.
- **C (Arduino IDE)**: linguagem utilizada para programação do ESP32.
- **HTML**: desenvolvimento da interface web.
- **MQTT** (opcional): protocolo leve para comunicação entre dispositivos, caso desejado.

## 🚀 Como Executar

1. Clone o repositório:

   ```bash
   git clone https://github.com/arrszera/TDE-ciberfisico.git
   ```

2. Abra o projeto na **Arduino IDE** ou **PlatformIO**.

3. Instale as bibliotecas necessárias:
   - `DHT sensor library`
   - `Adafruit Unified Sensor`
   - `WiFi` ou `WiFiManager` (dependendo da implementação).

4. Configure as credenciais da rede Wi-Fi no código fonte.

5. Compile e faça o upload para o **ESP32**.

6. Após a conexão do ESP32 à rede Wi-Fi, acesse o endereço IP informado pelo monitor serial para visualizar a interface web.

## 📁 Estrutura do Repositório

- `dhd22.c`: código para leitura do sensor de temperatura e umidade.
- `index.c`: página onde é rodado a versão integrada e final do código.
- `momento.c`: funções auxiliares do sistema.
- `testeBuzzer.c`: código de teste para acionamento de um buzzer.
- `index.html`: interface web para exibição dos dados monitorados.

## 📄 Licença

Este projeto está licenciado sob a licença **MIT**.

Sinta-se à vontade para usar, modificar e distribuir este código, desde que preserve os créditos ao autor.

[MIT License](https://opensource.org/licenses/MIT)

## ✍️ Autor

- [@arrszera](https://github.com/arrszera)
- [@LucasTheiss](https://github.com/LucasTheiss)
- [@rogergrzy](https://github.com/rogergrzy)
