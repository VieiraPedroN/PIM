<h1>Atenção você não deve incrementar outros codigos na branch *main*</h1>

<h2>
Quando você cria o codigo você utiliza um void main(){...} ou int main(){...} para realizar verificações e testes, se você for puxar o codigo para o menu.c você deve renomear  a função para evitar conflitos de nomes.<br><br>
Caso queira puxar os dados de um codigo pra incrementar ao menu você deve puxar o codigo via #include ex: <br><br>
Tenho um codigo com o nome fluxo_caixa.c e quero puxar o mesmo para o menu.c para um teste, devo usar #include "fluxo_caixa.c" no inicio do codigo do menu para  que ele possa ler o codigo do fluxo_caixa.c e em seguida renomear a função main para poder chamar a mesma no menu e poder testar no codigo main.<br><br></h2>