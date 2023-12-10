# SGDB-ITP

## Projeto de simulação de um sistema de banco de dados em C da disciplina introdução às técnicas de programação

Este projeto consiste em um sistema de banco de dados simples baseado no modelo relacional e implementado em linguagem C, desenvolvido como parte da disciplina de Introdução às Técnicas de Programação.

### Código-Fonte

O código-fonte inclui funcionalidades como criação de tabelas, inserção de dados, listagem de tabelas, criação de novas linhas em tabelas, listagem de dados de uma tabela, pesquisa de valores em uma tabela, exclusão de linhas em uma tabela e exclusão de tabelas.

### Principais Componentes (Header Files)

- **delete.c:** Contém funções relacionadas à exclusão de tabelas e linhas.
- **tabelas.c:** Define estruturas e funções para manipulação de tabelas, colunas e linhas.
- **pesquisas.c:** Implementa funções para listar dados e pesquisar valores em tabelas.
- **SGBD.c:** O arquivo principal contendo a função main() que interage com o usuário através de um menu de opções.

### Funcionalidades Principais

- **Criação de Tabelas:** Permite a definição de novas tabelas com colunas e chave primária.
- **Listagem de Tabelas:** Exibe todas as tabelas existentes.
- **Criação de Linhas:** Adiciona novas linhas com dados em uma tabela específica.
- **Listagem de Dados:** Exibe os dados de uma tabela selecionada.
- **Pesquisa de Valores:** Permite a busca por valores específicos em uma tabela.
- **Exclusão de Linhas:** Remove uma linha específica de uma tabela.
- **Exclusão de Tabelas:** Remove uma tabela específica.

### Execução

O programa deve ser compilado com o seguinte comando:  
```gcc SGBD.c tabelas.c delete.c pesquisas.c -o --nome_do_arquivo_executável-- ```
Seguindo de: 
```./--nome_do_arquivo_executável-- ```

O programa é executado através de um loop que exibe um menu de opções. O usuário pode escolher diferentes operações interativamente.

### Finalização

O programa encerra quando o usuário seleciona a opção de fechar (0).
