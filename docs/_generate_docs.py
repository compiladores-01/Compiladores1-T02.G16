# -*- coding: utf-8 -*-
from pathlib import Path

ROOT = Path(__file__).resolve().parent
PAGES = [
    ("index.html", "Projeto"),
    ("especificacao.html", "Especificação"),
    ("guia.html", "Guia"),
    ("planejamento.html", "Planejamento"),
    ("sprints.html", "Sprints"),
    ("atas.html", "Atas"),
    ("atividades.html", "Semanas"),
    ("decisoes.html", "Decisões"),
    ("problemas.html", "Problemas"),
    ("tokens.html", "Tokens"),
]


def nav(current):
    links = []
    for href, label in PAGES:
        cls = ' class="is-current"' if href == current else ""
        links.append(f'          <a href="{href}"{cls}>{label}</a>')
    return "\n".join(links)


def page(filename, title, description, kicker, heading, lead, meta, toc, sections, extra_head=""):
    toc_html = "\n".join(
        f'          <a href="#{sid}"{" class=\"is-current\"" if i == 0 else ""}><span>{i:02d}</span> {label}</a>'
        for i, (sid, label) in enumerate(toc)
    )
    html = f"""<!DOCTYPE html>
<html lang="pt-BR">
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta name="theme-color" content="#08110c">
    <meta name="description" content="{description}">
    <link rel="stylesheet" href="assets/css/styles.css">
    <title>{title} | Compiladores 1 — FGA0003</title>
    {extra_head}
  </head>
  <body>
    <header class="site-header">
      <nav class="top-nav" aria-label="Navegação principal">
        <a class="brand" href="index.html"><img class="brand__logo" src="assets/img/unb.jpg" alt="UnB">FGA0003 <span>/</span> COMPILADORES 1</a>
        <button class="nav-toggle" id="nav-toggle" type="button" aria-expanded="false" aria-controls="nav-menu">Menu</button>
        <div class="nav-menu" id="nav-menu">
{nav(filename)}
        </div>
      </nav>
    </header>

    <div class="document-shell" id="inicio">
      <aside class="contents" aria-label="Sumário">
        <p class="contents__heading">NESTA PÁGINA</p>
        <nav class="contents__nav">
{toc_html}
        </nav>
        <div class="contents__note">
          <span>PROJETO</span>
          <code>Python → C</code>
          <a class="text-link" href="https://github.com/Fernandavazgit1/-FGA0003Compiladores1-T02.G16">Repositório GitHub</a>
        </div>
      </aside>

      <main class="report">
        <article>
          <header class="report__header">
            <p class="kicker">{kicker}</p>
            <h1>{heading}</h1>
            <p class="report__lead">{lead}</p>
            <div class="metadata">
{meta}
            </div>
          </header>
{sections}
          <footer class="report-footer">
            <p>FGA0003 <span>—</span> COMPILADORES 1 · T02 · G16</p>
            <a class="text-link" href="index.html">Página do projeto ↑</a>
            <p class="copyright">Universidade de Brasília · FCTE · 2026/2</p>
          </footer>
        </article>
      </main>
    </div>
    <script src="assets/js/main.js"></script>
  </body>
</html>
"""
    (ROOT / filename).write_text(html, encoding="utf-8")


def sec(sid, index, kicker, title, body, last=False):
    cls = " report-section--last" if last else ""
    return f"""
          <section class="report-section{cls}" id="{sid}">
            <p class="section-index">{index} <span>/</span> {kicker}</p>
            <h2>{title}</h2>
            {body}
          </section>
"""


# ---------- INDEX ----------
page(
    "index.html",
    "Projeto",
    "Documentação do compilador Python para C da disciplina FGA0003 Compiladores 1.",
    "FGA0003 <span>/</span> T02 · G16",
    "Compilador <em>Python → C</em>",
    "Documentação do tradutor de um subconjunto de Python para C, desenvolvido com Flex e Bison na disciplina Compiladores 1 (2026/2).",
    """              <p><span>Curso</span>Engenharia de Software · FCTE / UnB</p>
              <p><span>Professor</span>Dr. Sergio Antônio Andrade de Freitas</p>
              <p><span>Equipe</span>3 integrantes · turma T02</p>""",
    [
        ("projeto", "Sobre o projeto"),
        ("equipe", "Equipe"),
        ("pipeline", "Pipeline"),
        ("executar", "Como executar"),
        ("estado", "Estado atual"),
        ("documentacao", "Documentação"),
    ],
    sec("projeto", "00", "INTRODUÇÃO", "Sobre o projeto", """
            <div class="hero-logos"><img src="assets/img/python-c.jpg" alt="Logos de Python e C"></div>
            <p>A disciplina aborda os princípios da construção de compiladores e o processamento de linguagens. Como aplicação prática, a equipe constrói um compilador de um subconjunto de Python para C, com análise léxica (Flex), análise sintática (Bison), AST, tabela de símbolos, checagens semânticas e geração de código C.</p>
            <div class="table-scroll">
              <table class="document-table">
                <thead><tr><th>Atributo</th><th>Detalhes</th></tr></thead>
                <tbody>
                  <tr><th scope="row">Curso</th><td>Engenharia de Software (FCTE — UnB)</td></tr>
                  <tr><th scope="row">Turma</th><td>T02 · grupo G16</td></tr>
                  <tr><th scope="row">Carga horária</th><td>60 horas</td></tr>
                  <tr><th scope="row">Professor</th><td>Dr. Sergio Antônio Andrade de Freitas</td></tr>
                  <tr><th scope="row">Alvo</th><td>Traduzir um subconjunto de Python para C</td></tr>
                  <tr><th scope="row">Ferramentas</th><td>Flex, Bison, GCC e Make</td></tr>
                </tbody>
              </table>
            </div>
            <a class="external-link" href="https://github.com/Fernandavazgit1/-FGA0003Compiladores1-T02.G16">github.com/Fernandavazgit1/-FGA0003Compiladores1-T02.G16</a>
    """)
    + sec("equipe", "01", "PESSOAS", "Membros da equipe", """
            <div class="team-grid">
              <div class="team-card"><span>221007715</span><h3>Fernanda Vaz</h3><p>Léxico, integração e documentação.</p></div>
              <div class="team-card"><span>200023535</span><h3>Manoel Castro</h3><p>Parser, gramática e erros sintáticos.</p></div>
              <div class="team-card"><span>222006623</span><h3>Cauã Clemente</h3><p>AST, semântica e geração de C.</p></div>
            </div>
            <p>A equipe tem três integrantes. Papéis rotacionam nas sprints, mas cada pessoa mantém uma frente principal. Reuniões semanais às quartas, alinhadas às aulas práticas da disciplina.</p>
    """)
    + sec("pipeline", "02", "ARQUITETURA", "Pipeline do compilador", """
            <p>O fluxo implementado no repositório percorre o programa Python até um arquivo C compilável pelo GCC. A geração é feita a partir da AST, com checagens semânticas no parser.</p>
            <div class="pipeline">
              <div><strong>.py</strong><span>entrada</span></div>
              <div><strong>Flex</strong><span>tokens</span></div>
              <div><strong>Bison</strong><span>gramática</span></div>
              <div><strong>AST</strong><span>árvore</span></div>
              <div><strong>Semântica</strong><span>tipos / escopo</span></div>
              <div><strong>Codegen</strong><span>emissão C</span></div>
              <div><strong>.c + gcc</strong><span>saída</span></div>
            </div>
            <div class="code-block">
              <div class="code-block__header"><span>PIPELINE</span><span>compilador/</span></div>
              <pre><code>programa.py → Flex → tokens → Bison → AST → análise semântica → código C</code></pre>
            </div>
            <p>Arquivos centrais: <code>lexer/lexer.l</code>, <code>parser/parser.y</code>, <code>ast.c</code>, <code>tabela.c</code> e <code>geracao.c</code>.</p>
    """)
    + sec("executar", "03", "USO", "Como executar", """
            <p>É necessário ter Flex, Bison, GCC e Make. No Linux/WSL:</p>
            <div class="code-block">
              <div class="code-block__header"><span>BASH</span><span>dependências</span></div>
              <pre><code>sudo apt-get update
sudo apt-get install flex bison build-essential</code></pre>
            </div>
            <div class="code-block">
              <div class="code-block__header"><span>BASH</span><span>compilar e rodar</span></div>
              <pre><code>git clone https://github.com/Fernandavazgit1/-FGA0003Compiladores1-T02.G16.git
cd -FGA0003Compiladores1-T02.G16/compilador
make
./compilador-bin entrada.py saida.c
gcc saida.c -o saida_prog
./saida_prog</code></pre>
            </div>
            <p>No Windows, use WSL2 ou MSYS2 MinGW64. O exemplo <code>entrada.py</code> cobre <code>while</code>, função <code>def</code>, <code>if/else</code> e <code>print</code>.</p>
    """)
    + sec("estado", "04", "STATUS", "Estado atual", """
            <p>O compilador já implementa o subconjunto combinado nas sprints: variáveis, expressões, impressão, condicionais, laços, funções, análise semântica e geração de C.</p>
            <ul class="status-list">
              <li><span class="badge">PRONTO</span>Tokens, indentação INDENT/DEDENT, operadores relacionais e palavras-chave <code>def</code>/<code>return</code></li>
              <li><span class="badge">PRONTO</span>Parser com blocos por indentação, AST e tabela de símbolos com escopos</li>
              <li><span class="badge">PRONTO</span>Checagens de tipo, variável não definida, <code>return</code> fora de função e funções aninhadas</li>
              <li><span class="badge">PRONTO</span>Emissão de C com <code>printf</code>, <code>if/else</code>, <code>while</code> e funções</li>
              <li><span class="badge badge--warn">LIMITAÇÃO</span>Sem IR de três endereços separada: o backend percorre a AST. Sem classes, listas ou funções aninhadas</li>
            </ul>
    """)
    + sec("documentacao", "05", "ÍNDICE", "Documentação do projeto", """
            <p>Todo o material de MkDocs foi trazido para este layout e atualizado conforme o código do repositório do compilador.</p>
            <div class="doc-grid">
              <a class="doc-card" href="especificacao.html"><span>01</span><strong>Especificação</strong><p>Objetivo, requisitos oficiais, escopo da subset e critérios de aceite.</p></a>
              <a class="doc-card" href="guia.html"><span>02</span><strong>Guia detalhado</strong><p>Passos de construção alinhados ao guia da disciplina.</p></a>
              <a class="doc-card" href="planejamento.html"><span>03</span><strong>Planejamento</strong><p>Metodologia, ferramentas, cronograma e mapa das sprints.</p></a>
              <a class="doc-card" href="sprints.html"><span>04</span><strong>Sprints</strong><p>Histórico Scrum, da organização até a finalização.</p></a>
              <a class="doc-card" href="atas.html"><span>05</span><strong>Atas</strong><p>Registros das reuniões e mudanças de linguagem.</p></a>
              <a class="doc-card" href="atividades.html"><span>06</span><strong>Atividades semanais</strong><p>Práticas da disciplina ligadas ao compilador.</p></a>
              <a class="doc-card" href="decisoes.html"><span>07</span><strong>Decisões técnicas</strong><p>Justificativas de arquitetura e design.</p></a>
              <a class="doc-card" href="problemas.html"><span>08</span><strong>Problemas e soluções</strong><p>Impedimentos reais encontrados no código.</p></a>
              <a class="doc-card" href="pontos.html"><span>09</span><strong>Pontos de controle</strong><p>Checklists de P1 e P2.</p></a>
              <a class="doc-card" href="tokens.html"><span>10</span><strong>Tokens</strong><p>Referência do analisador léxico atualizado.</p></a>
            </div>
    """, last=True),
)

# ---------- ESPECIFICACAO ----------
page(
    "especificacao.html",
    "Especificação",
    "Especificação do compilador Python para C.",
    "PROJETO FINAL <span>/</span> ESPECIFICAÇÃO",
    "Especificação do <em>projeto</em>",
    "Especificação da equipe com base na proposta de trabalho de Compiladores 1 e no plano de ensino 2026/2, alinhada ao código do grupo G16.",
    """              <p><span>Tipo</span>Compilador</p>
              <p><span>Fonte</span>Subconjunto de Python</p>
              <p><span>Alvo</span>C · Flex + Bison</p>""",
    [
        ("objetivo", "Objetivo"),
        ("equipe", "Organização"),
        ("requisitos", "Requisitos"),
        ("escopo", "Escopo"),
        ("aceite", "Critérios de aceite"),
        ("avaliacao", "Avaliação"),
    ],
    sec("objetivo", "00", "TRABALHO", "Objetivo", """
            <p>Desenvolver, ao longo do semestre, um compilador que traduza programas de um subconjunto de Python para C, cobrindo análise léxica e sintática, AST, tabela de símbolos, análise semântica e geração de código.</p>
            <p>O trabalho inclui planejamento, implementação, testes e documentação. Toda decisão relevante precisa ser justificada.</p>
    """)
    + sec("equipe", "01", "GRUPO", "Formação e organização", """
            <p>Equipe de três estudantes, dentro do limite da disciplina (até cinco). Projeto definido como compilador Python → C, não interpretador. Organização em Scrum com sprints documentadas.</p>
            <div class="table-scroll">
              <table class="document-table">
                <thead><tr><th>Papel</th><th>Foco</th></tr></thead>
                <tbody>
                  <tr><th>Integração e léxico</th><td>Prazos, Flex, tokens da subset</td></tr>
                  <tr><th>Sintaxe / AST</th><td>Bison, erros, árvore</td></tr>
                  <tr><th>Semântica / codegen</th><td>Tabela de símbolos e emissão C</td></tr>
                </tbody>
              </table>
            </div>
    """)
    + sec("requisitos", "02", "DISCIPLINA", "Requisitos oficiais", """
            <h3>Repositório GitHub</h3>
            <p>Usado durante todo o desenvolvimento. A documentação precisa conter estrutura, decisões, planejamento das sprints, problemas e soluções, atas e acompanhamento.</p>
            <h3>Pontos de controle</h3>
            <p><strong>P1:</strong> definição do projeto, linguagem e subset, planejamento e o que já foi implementado. Formulário até 23/09/2026, 23h59. Apresentação em 28/09 e 30/09.</p>
            <p><strong>P2:</strong> funcionalidades principais, melhorias desde P1 e ajustes no planejamento. Formulário até 04/11/2026, 23h59. Apresentação em 09/11 e 11/11.</p>
            <div class="callout callout--warning"><strong>Atenção</strong><p>Não envio do formulário no prazo implica nota 0 naquele ponto de controle. Presença de todos os membros é obrigatória em P1, P2 e na entrevista final (T).</p></div>
            <h3>Entrega final (T)</h3>
            <p>Projeto no GitHub e entrevista presencial sobre funcionamento, justificativa das decisões e dificuldades. Datas: 30/11 e 02/12/2026.</p>
    """)
    + sec("escopo", "03", "LINGUAGEM", "Subconjunto Python → C", """
            <div class="table-scroll">
              <table class="document-table">
                <thead><tr><th>Construção Python</th><th>Tradução C</th><th>Status no código</th></tr></thead>
                <tbody>
                  <tr><th>Literais int, float, str, bool</th><td>int / double / const char* / int 0-1</td><td>Implementado</td></tr>
                  <tr><th>Atribuição e expressões</th><td>Declarações e expressões C</td><td>Implementado</td></tr>
                  <tr><th>if / else e while</th><td>if / else / while</td><td>Implementado, com INDENT/DEDENT</td></tr>
                  <tr><th>print(...)</th><td>printf com formato por tipo</td><td>Implementado</td></tr>
                  <tr><th>def / return / chamada</th><td>Função C e return</td><td>Implementado; sem aninhamento</td></tr>
                  <tr><th>Operadores relacionais</th><td>== != &lt; &gt; &lt;= &gt;=</td><td>Implementado</td></tr>
                </tbody>
              </table>
            </div>
            <p>Fora do escopo: classes, comprehensions, async, tipagem estática completa, imports, listas, dicionários e exceções avançadas.</p>
    """)
    + sec("aceite", "04", "MARCOS", "Critérios de aceite", """
            <h3>Até P1</h3>
            <ul class="checklist">
              <li class="done">Repositório e documentação ativos</li>
              <li class="done">Lexer Flex reconhecendo a subset</li>
              <li class="done">Parser Bison aceitando programas mínimos</li>
              <li class="done">AST demonstrável</li>
            </ul>
            <h3>Até P2 / T</h3>
            <ul class="checklist">
              <li class="done">Análise semântica integrada no parser</li>
              <li class="done">Geração de C a partir da AST</li>
              <li class="done">Exemplos .py → .c compiláveis no GCC</li>
              <li class="open">IR de três endereços ainda não adotada como fase separada</li>
            </ul>
    """)
    + sec("avaliacao", "05", "NOTA", "Avaliação", """
            <p>NF = (P1 + 2·P2 + 3·C + 4·T) / 10. Aprovação com NF ≥ 5,0 e pelo menos 75% de presença.</p>
            <p>Recomendações adotadas: projeto definido cedo, Scrum, commits frequentes, guias da disciplina, quartas para integração e documentação de decisões — qualquer integrante pode ser sorteado na entrevista.</p>
    """, last=True),
)

# ---------- GUIA ----------
page(
    "guia.html",
    "Guia detalhado",
    "Roteiro de implementação do compilador Python para C.",
    "PROJETO FINAL <span>/</span> GUIA",
    "Guia <em>detalhado</em>",
    "Roteiro adaptado do guia da disciplina e da proposta PBL + Scrum, agora descrito com o que o repositório G16 realmente implementa.",
    """              <p><span>Equipe</span>3 pessoas</p>
              <p><span>Ferramentas</span>Flex + Bison</p>
              <p><span>Alvo</span>C (GCC)</p>""",
    [
        ("arquitetura", "Arquitetura"),
        ("passos", "Passos"),
        ("sprints-guia", "Sprints do guia"),
        ("ritual", "Ritual Scrum"),
        ("checklist", "Checklist"),
    ],
    sec("arquitetura", "00", "VISÃO", "Arquitetura", """
            <div class="code-block">
              <div class="code-block__header"><span>FLUXO</span><span>implementado</span></div>
              <pre><code>arquivo.py
  → Flex (análise léxica, NEWLINE, INDENT, DEDENT)
  → Bison (gramática + ações semânticas)
  → AST (ast.c / ast.h)
  → tabela de símbolos (tabela.c)
  → geracao.c → arquivo.c
  → gcc</code></pre>
            </div>
            <p>O guia da disciplina prevê IR e otimizações opcionais. Neste projeto a geração de C percorre a AST diretamente. Constant folding e TAC ficam como melhoria, não como fase obrigatória do binário atual.</p>
    """)
    + sec("passos", "01", "CONSTRUÇÃO", "Passos de construção", """
            <ol class="numbered-list">
              <li>Definir a subset Python e exemplos canônicos (<code>entrada.py</code>).</li>
              <li>Análise léxica com Flex: ids, keywords, literais, operadores, comentários <code>#</code> e indentação.</li>
              <li>Parser Bison com blocos <code>NEWLINE INDENT ... DEDENT</code> e construção da AST nas ações.</li>
              <li>Semântica na própria gramática: tipos, símbolos, funções e mensagens em stderr.</li>
              <li>Geração de C: declarações inferidas, <code>printf</code> por tipo, concatenação de strings via helper, divisão sempre em <code>double</code>.</li>
              <li>Testar com <code>make</code> e <code>gcc saida.c</code>.</li>
            </ol>
    """)
    + sec("sprints-guia", "02", "DISCIPLINA", "Mapeamento das 6 sprints do guia", """
            <div class="table-scroll">
              <table class="document-table">
                <thead><tr><th>Guia</th><th>Foco</th><th>No nosso projeto</th></tr></thead>
                <tbody>
                  <tr><th>Sprint 1</th><td>Fundação</td><td>S0: ambiente, subset e MkDocs</td></tr>
                  <tr><th>Sprint 2</th><td>Léxico + parser + P1</td><td>S1–S4</td></tr>
                  <tr><th>Sprint 3</th><td>AST e semântica inicial</td><td>S3–S5</td></tr>
                  <tr><th>Sprint 4</th><td>Semântica + IR + P2</td><td>S5–S6; IR substituída por codegen direto</td></tr>
                  <tr><th>Sprint 5</th><td>Otimização + C</td><td>S6–S7: geracao.c</td></tr>
                  <tr><th>Sprint 6</th><td>Entrevista T</td><td>S8–S9 e entrega final</td></tr>
                </tbody>
              </table>
            </div>
    """)
    + sec("ritual", "03", "SCRUM", "Ritual nas quartas", """
            <ol class="numbered-list">
              <li>Daily rápida: o que fiz / farei / bloqueio.</li>
              <li>Hands-on no compilador (integração e PRs).</li>
              <li>Review ao fim da sprint.</li>
              <li>Atualizar atas, problemas, decisões e semanas.</li>
            </ol>
    """)
    + sec("checklist", "04", "DOCS", "Checklist de documentação", """
            <ul class="checklist">
              <li class="done">Estrutura do projeto</li>
              <li class="done">Decisões técnicas</li>
              <li class="done">Planejamento das sprints</li>
              <li class="done">Problemas e soluções</li>
              <li class="done">Atas e atividades semanais</li>
              <li class="done">Pontos de controle</li>
              <li class="done">Referência de tokens alinhada ao lexer atual</li>
            </ul>
    """, last=True),
)

# ---------- PLANEJAMENTO ----------
page(
    "planejamento.html",
    "Planejamento",
    "Metodologia, ferramentas, cronograma e planejamento das sprints.",
    "PROCESSO <span>/</span> PLANEJAMENTO",
    "Planejamento do <em>semestre</em>",
    "Metodologia PBL + Scrum, stack Flex/Bison, cronograma alinhado ao plano de ensino e mapa das sprints da equipe de três pessoas.",
    """              <p><span>Aulas</span>Segunda e quarta, 16h–17h50</p>
              <p><span>Sala</span>I10</p>
              <p><span>Sprints</span>0 a 9</p>""",
    [
        ("metodologia", "Metodologia"),
        ("ferramentas", "Ferramentas"),
        ("cronograma", "Cronograma"),
        ("sprints-mapa", "Mapa das sprints"),
        ("bibliografia", "Bibliografia"),
    ],
    sec("metodologia", "00", "PBL", "Metodologia", """
            <p>A disciplina combina aulas expositivas e Problem Based Learning. A equipe aplica o mesmo ciclo ao compilador Python → C.</p>
            <div class="table-scroll">
              <table class="document-table">
                <thead><tr><th>Dia</th><th>Tipo</th><th>Uso pela equipe</th></tr></thead>
                <tbody>
                  <tr><th>Segunda 16h–17h50</th><td>Teórica</td><td>Alinhar autômatos, GLC, semântica e geração ao design</td></tr>
                  <tr><th>Quarta 16h–17h50</th><td>Prática / PBL</td><td>Implementar, integrar e testar incrementos</td></tr>
                </tbody>
              </table>
            </div>
            <p>Material: <a class="text-link" href="https://slides.cedis.tec.br/c/sergio-compiladores">slides CEDIS</a> · <a class="text-link" href="https://github.com/sergioaafreitas/COMP1">sergioaafreitas/COMP1</a>.</p>
            <h3>Ritmo semanal</h3>
            <ul class="document-list">
              <li>Após a segunda: atualizar backlog com o tema teórico.</li>
              <li>Quarta: coding session coletivo.</li>
              <li>Até domingo: fechar PRs/issues e atualizar docs.</li>
              <li>Antes de P1/P2/T: ensaio da apresentação.</li>
            </ul>
            <h3>Qualidade interna</h3>
            <p>Código compilável a partir do README, subset documentada, exemplos <code>.py</code>/<code>.c</code> versionados e este site refletindo o estado real do repositório.</p>
    """)
    + sec("ferramentas", "01", "STACK", "Ferramentas", """
            <div class="technology-list">
              <div><p class="tech-label">LÉXICO</p><h3>Flex</h3><p>Tokens, palavras-chave, literais, NEWLINE e indentação.</p></div>
              <div><p class="tech-label">SINTAXE</p><h3>Bison</h3><p>GLC da subset, AST e checagens semânticas nas ações.</p></div>
              <div><p class="tech-label">BACKEND</p><h3>GCC / Make</h3><p>Compila o compilador e o C gerado.</p></div>
            </div>
            <div class="table-scroll">
              <table class="document-table">
                <thead><tr><th>Ferramenta</th><th>Uso</th></tr></thead>
                <tbody>
                  <tr><th>Git / GitHub</th><td>Versionamento, PRs e issues</td></tr>
                  <tr><th>Este site</th><td>Documentação no layout do projeto (substitui o MkDocs na apresentação)</td></tr>
                  <tr><th>Forms Office</th><td>Formulários P1 e P2 pelo líder</td></tr>
                  <tr><th>Markdown</th><td>Fonte original das atas, sprints e decisões</td></tr>
                </tbody>
              </table>
            </div>
            <p>Ambiente recomendado: Linux ou WSL2. Alternativa no Windows: MSYS2 MinGW64.</p>
    """)
    + sec("cronograma", "02", "CALENDÁRIO", "Cronograma", """
            <div class="callout"><strong>Datas-chave</strong><p>P1 formulário 23/09 · P1 apresentação 28 e 30/09 · P2 formulário 04/11 · P2 apresentação 09 e 11/11 · Entrevista T 30/11 e 02/12/2026.</p></div>
            <div class="table-scroll">
              <table class="document-table">
                <thead><tr><th>Fase</th><th>Período</th><th>Foco</th><th>Marco</th></tr></thead>
                <tbody>
                  <tr><th>Fundação</th><td>10/08 – 26/08</td><td>Ambiente, subset, lexer</td><td>Scanner inicial</td></tr>
                  <tr><th>Sintaxe</th><td>31/08 – 16/09</td><td>Parser, erros, AST</td><td>Front-end</td></tr>
                  <tr><th>P1</th><td>23/09 – 30/09</td><td>Consolidação</td><td>Entrega P1</td></tr>
                  <tr><th>Semântica</th><td>05/10 – 14/10</td><td>Tipos e escopos</td><td>Pipeline intermediário</td></tr>
                  <tr><th>Código</th><td>19/10 – 28/10</td><td>Geração de C</td><td>Backend</td></tr>
                  <tr><th>P2</th><td>04/11 – 11/11</td><td>Integração</td><td>Entrega P2</td></tr>
                  <tr><th>Fechamento</th><td>16/11 – 25/11</td><td>Testes e docs</td><td>Compilador final</td></tr>
                  <tr><th>T</th><td>30/11 – 02/12</td><td>Entrevista</td><td>Nota C + T</td></tr>
                </tbody>
              </table>
            </div>
            <p>Agosto: tokens e milestone M1. Setembro: gramática, <code>yyerror</code>, AST e P1. Outubro: semântica e emissão de C. Novembro: P2, polimento e T.</p>
    """)
    + sec("sprints-mapa", "03", "SCRUM", "Mapa das sprints da equipe", """
            <p>Há dois recortes na documentação original: um mapa de ~2 semanas (S0–S8) e sprints semanais (0–9) usadas nos arquivos <code>sprint-0X.md</code>. Este site usa as sprints semanais, que batem com o histórico do repositório.</p>
            <div class="table-scroll">
              <table class="document-table">
                <thead><tr><th>Sprint</th><th>Período</th><th>Objetivo</th></tr></thead>
                <tbody>
                  <tr><th>0</th><td>26/08 – 01/09</td><td>Organização, escopo e ambiente</td></tr>
                  <tr><th>1</th><td>02/09 – 08/09</td><td>Analisador léxico</td></tr>
                  <tr><th>2</th><td>09/09 – 15/09</td><td>Analisador sintático</td></tr>
                  <tr><th>3</th><td>16/09 – 22/09</td><td>AST e integração</td></tr>
                  <tr><th>4</th><td>23/09 – 29/09</td><td>P1 e semântica inicial</td></tr>
                  <tr><th>5</th><td>30/09 – 06/10</td><td>Análise semântica</td></tr>
                  <tr><th>6</th><td>07/10 – 13/10</td><td>Geração de C</td></tr>
                  <tr><th>7</th><td>14/10 – 20/10</td><td>Integração completa</td></tr>
                  <tr><th>8</th><td>21/10 – 27/10</td><td>Testes e correções</td></tr>
                  <tr><th>9</th><td>28/10 – 03/11</td><td>Finalização e documentação</td></tr>
                </tbody>
              </table>
            </div>
    """)
    + sec("bibliografia", "04", "REFERÊNCIAS", "Bibliografia", """
            <p><strong>Básica:</strong> Tremblay &amp; Sorenson — <em>Theory and Practice of Compiler Writing</em>; Wirth — <em>Compiler Construction</em>; Singh — <em>Design and Implementation of Compiler</em>.</p>
            <p><strong>Complementar:</strong> Subramanian; Herrera / Casa Novas; Martin-Vide; Kowaltowski — <em>Implementação de Linguagens de Programação</em>.</p>
    """, last=True),
)

# ---------- SPRINTS ----------
sprint_items = [
    ("S0", "26/08 – 01/09", "Organização e planejamento",
     "<p>Preparar o projeto, definir o subconjunto Python, arquitetura e ambiente Flex/Bison/GCC/Make. Criar GitHub Project, labels, milestones e padrão de branches.</p><p><strong>Concluído:</strong> estrutura do repositório, fluxo do compilador e documentação inicial. <strong>Decisão:</strong> sprints semanais e linguagem alvo C.</p>"),
    ("S1", "02/09 – 08/09", "Analisador léxico",
     "<p>Implementar <code>lexer.l</code>: identificadores, inteiros, floats, strings, keywords, operadores, delimitadores, comentários, linhas, INDENT/DEDENT e erros léxicos.</p><p>No código atual o lexer também reconhece <code>True</code>/<code>False</code>, relacionais e enfileira INDENT/DEDENT no início de linha.</p>"),
    ("S2", "09/09 – 15/09", "Analisador sintático",
     "<p>Criar <code>parser.y</code>, integrar lexer e parser, atribuições, expressões, precedência, <code>print</code>, <code>if/else</code>, <code>while</code>, funções, <code>return</code>, chamadas, blocos e <code>yyerror</code>.</p>"),
    ("S3", "16/09 – 22/09", "AST e integração",
     "<p>Nós em <code>ast.h</code> para programa, expressões, atribuição, print, if, while, função, return e chamada. Dump da AST e testes de integração.</p>"),
    ("S4", "23/09 – 29/09", "P1 e semântica inicial",
     "<p>Revisar front-end, preparar demo P1, definir tabela de símbolos e tipos. Formulário P1 até 23/09.</p>"),
    ("S5", "30/09 – 06/10", "Análise semântica",
     "<p>Registrar variáveis e funções, escopos, busca, tipos, operações, comparações, chamadas e <code>return</code> fora de função. Mensagens <code>Erro semantico:</code>.</p>"),
    ("S6", "07/10 – 13/10", "Geração de C",
     "<p><code>geracao.c</code> emite declarações, expressões, <code>printf</code> por tipo, concatenação de strings, <code>if/else</code>, <code>while</code> e funções. Divisão Python vira divisão real em C.</p>"),
    ("S7", "14/10 – 20/10", "Integração completa",
     "<p>CLI <code>./compilador-bin entrada.py saida.c</code>, Makefile e pipeline ponta a ponta. Semântica impede gerar C se houver erros.</p>"),
    ("S8", "21/10 – 27/10", "Testes e correções",
     "<p>Casos positivos (variáveis, laços, funções) e negativos (léxico, sintaxe, indentação, tipos, função inexistente). Refatorar mensagens e warnings.</p>"),
    ("S9", "28/10 – 03/11", "Finalização",
     "<p>Revisão de arquitetura, README, este site, limitações, issues e ensaio da apresentação.</p>"),
]
accordion = '<div class="accordion">' + "".join(
    f'<details><summary>{num} · {periodo} — {titulo}</summary><div class="accordion__body"><p class="meta-row"><span>{periodo}</span></p>{corpo}</div></details>'
    for num, periodo, titulo, corpo in sprint_items
) + "</div>"

page(
    "sprints.html",
    "Sprints",
    "Metodologia Scrum e registro das sprints do compilador.",
    "PROCESSO <span>/</span> SCRUM",
    "Sprints do <em>compilador</em>",
    "Desenvolvimento em sprints semanais, com issues no GitHub, revisão por outro integrante e registro de objetivo, impedimentos e resultado.",
    """              <p><span>Método</span>Scrum</p>
              <p><span>Reunião</span>Quarta-feira</p>
              <p><span>Equipe</span>3 integrantes</p>""",
    [
        ("scrum", "Scrum"),
        ("visao", "Visão geral"),
        ("distribuicao", "Tarefas"),
        ("github", "Fluxo GitHub"),
    ],
    sec("scrum", "00", "MÉTODO", "Como a equipe trabalha", """
            <p>Cada sprint tem objetivo, tarefas, issues, acompanhamento, problemas e documentação. Antes da reunião de quarta, cada pessoa atualiza issues, commits e PRs.</p>
            <p>A reunião verifica o feito, atrasos, impedimentos, progresso, próximas atividades, GitHub Project e decisões técnicas.</p>
    """)
    + sec("visao", "01", "MAPA", "Visão geral", """
            <p>As sprints acompanham o compilador da organização até a entrega: léxico, sintaxe, AST, P1, semântica, geração de C, integração, testes e docs.</p>
    """)
    + sec("distribuicao", "02", "PAPÉIS", "Distribuição de tarefas", """
            <div class="table-scroll">
              <table class="document-table">
                <thead><tr><th>Área</th><th>Fernanda</th><th>Manoel</th><th>Cauã</th></tr></thead>
                <tbody>
                  <tr><th>Lexer</th><td>Principal</td><td>Apoio</td><td>Apoio</td></tr>
                  <tr><th>Parser</th><td>Apoio</td><td>Principal</td><td>Apoio</td></tr>
                  <tr><th>AST / semântica / C</th><td>Apoio</td><td>Apoio</td><td>Principal</td></tr>
                  <tr><th>Integração, testes e docs</th><td>Sim</td><td>Sim</td><td>Sim</td></tr>
                </tbody>
              </table>
            </div>
    """)
    + sec("github", "03", "GIT", "Fluxo no GitHub", """
            <div class="code-block"><pre><code>Issue → responsável → desenvolvimento → commit → PR → revisão → merge → issue fechada</code></pre></div>
            <p>Nenhuma alteração importante entra na branch principal sem revisão de outro integrante.</p>
    """, last=True),
)

# ---------- ATAS ----------
page(
    "atas.html",
    "Atas",
    "Atas das reuniões da equipe G16.",
    "ACOMPANHAMENTO <span>/</span> ATAS",
    "Atas das <em>reuniões</em>",
    "Registros das reuniões. As atas 2 e 3 documentam a mudança de linguagem-alvo; as atas 4 e 5 ainda não foram preenchidas na fonte original.",
    """              <p><span>Equipe</span>Fernanda, Manoel e Cauã</p>
              <p><span>Atas</span>5 registros</p>""",
    [
        ("ata1", "Ata 1"),
        ("ata2", "Ata 2"),
        ("ata3", "Ata 3"),
        ("ata4", "Atas 4 e 5"),
    ],
    sec("ata1", "00", "12/09/2026", "Ata 1 — alinhamento", """
            <p class="meta-row"><span>Participantes: Fernanda Vaz, Manoel Castro, Cauã Clemente</span></p>
            <p><strong>Pauta:</strong> integração dos integrantes e alinhamento inicial.</p>
            <ul class="document-list">
              <li>Definição da proposta e divisão inicial de tarefas.</li>
              <li>Escopo do compilador Python → C.</li>
              <li>Organização da documentação e do fluxo de trabalho.</li>
            </ul>
            <p><strong>Decisões:</strong> sprints semanais, documentação em site, início pelo analisador léxico, revisão nas reuniões.</p>
            <p><strong>Próximos passos:</strong> ambiente, lexer, primeiros tokens, GitHub Project.</p>
            <div class="callout"><strong>Nota de consistência</strong><p>A data registrada na ata (12/09) é posterior às atas 2 e 3 (agosto/setembro). Mantida como no documento original; o conteúdo descreve o kickoff da equipe.</p></div>
    """)
    + sec("ata2", "01", "19/08", "Ata 2 — decisão de linguagem", """
            <p>Prática de analisadores léxicos simples (expressões regulares). Participantes: Fernanda, Manoel e Cauã.</p>
            <p>A ata original registrou a ideia de Python para JavaScript. Esse alvo foi abandonado na reunião seguinte.</p>
            <p><strong>Próximos passos na época:</strong> preparar o ambiente de desenvolvimento.</p>
    """)
    + sec("ata3", "02", "02/09", "Ata 3 — Python para C", """
            <p>Pauta: mudança de linguagem e início da implementação.</p>
            <p><strong>Decisão:</strong> compilador de um subconjunto de Python para C, com Flex e Bison — alvo que permanece no repositório.</p>
            <p><strong>Próximos passos:</strong> iniciar o lexer.</p>
    """)
    + sec("ata4", "03", "PENDENTE", "Atas 4 e 5", """
            <p>Os arquivos originais <code>ata4.md</code> e <code>ata5.md</code> estão só com o template (data, participantes, pauta, decisões e próximos passos em branco).</p>
            <p>Sugestão para as próximas reuniões: registrar revisão do pipeline completo, bugs de indentação/semântica e preparação de P2/T.</p>
    """, last=True),
)

# ---------- ATIVIDADES ----------
weeks = [
    ("1", "Semana 01", "Hello Flex/Bison", "Glossário, guias de ambiente, compilador e interpretador, proposta do trabalho. Prática: hello.l / hello.y.",
     "Ambiente configurado, Hello World compilando, subset Python → C confirmada."),
    ("2", "Semana 02", "Expressões regulares", "Guia de ERs no Flex; exemplo que reconhece números e operadores.",
     "Tokens da subset esboçados em lexer.l; Makefile inspirado na prática."),
    ("3", "Semana 03", "Scanner", "scanner.l com if/while, ids, números, operadores e comentários C.",
     "Adaptado para keywords Python, comentários # e tokens consumidos pelo Bison."),
    ("4", "Semana 04", "Parser inicial", "Expressões com precedência * / sobre + -.",
     "parser.y da subset, precedência e Makefile integrando lexer + parser."),
    ("5", "Semana 05", "Erros sintáticos", "Recuperação via error até ;, yyerrok / yyclearin.",
     "No Python usamos NEWLINE/INDENT em vez de ponto e vírgula. yyerror reporta a linha; recuperação completa ainda é melhoria."),
    ("6", "Semana 06", "AST e tabela", "ast.c, tabela.c e tipos.h a partir de expressões com identificadores.",
     "Nós de stmt Python e tabela com escopos; base da semântica e do codegen. Marco P1."),
    ("7", "Semana 07", "Semântica", "Testes de variável não declarada, redeclaração e tipos.",
     "Regras no parser.y; mensagens claras para demo P2. Suíte tests/ ainda pode crescer."),
    ("8", "Semana 08", "IR / TAC", "Protótipo de três endereços na disciplina.",
     "A equipe optou por emitir C direto da AST, sem TAC no binário atual."),
    ("9", "Semana 09", "Otimização", "Constant folding sobre a AST.",
     "Não está no gerador atual; documentada como melhoria."),
    ("10", "Semana 10", "Código final", "Exemplo Java mínimo → bitcode textual.",
     "No nosso caso o alvo é C: percorrer AST e emitir saida.c, depois gcc."),
]
week_acc = '<div class="accordion">' + "".join(
    f'<details><summary>Semana {n} — {titulo}</summary><div class="accordion__body"><p><strong>Material:</strong> {mat}</p><p><strong>No projeto G16:</strong> {proj}</p></div></details>'
    for n, _, titulo, mat, proj in weeks
) + "</div>"

page(
    "atividades.html",
    "Atividades semanais",
    "Atividades semanais da disciplina ligadas ao compilador.",
    "ACOMPANHAMENTO <span>/</span> SEMANAS",
    "Atividades <em>semanais</em>",
    "Cada semana do repositório da disciplina vira prática no compilador Python → C. Os checklists originais foram atualizados com o estado do código.",
    """              <p><span>Fonte</span>sergioaafreitas/COMP1</p>
              <p><span>Semanas</span>1 a 10</p>""",
    [
        ("como", "Como usar"),
        ("semanas", "Semanas 1–10"),
    ],
    sec("como", "00", "DISCIPLINA", "Como usar as práticas", """
            <p>O repositório <a class="text-link" href="https://github.com/sergioaafreitas/COMP1">COMP1</a> traz um exemplo por semana. A equipe replica a ideia no próprio <code>compilador/</code>, em vez de entregar os exemplos isolados.</p>
            <div class="code-block"><pre><code>git clone https://github.com/sergioaafreitas/COMP1.git
cd "COMP1/semana 01/src"</code></pre></div>
    """)
    + sec("semanas", "01", "DIÁRIO", "Relação com o compilador", week_acc, last=True),
)

# ---------- DECISOES ----------
page(
    "decisoes.html",
    "Decisões técnicas",
    "Decisões técnicas do compilador Python para C.",
    "ENGENHARIA <span>/</span> DECISÕES",
    "Decisões <em>técnicas</em>",
    "Toda escolha relevante do compilador Python → C precisa de contexto, alternativas, decisão e consequências — requisito da entrevista final.",
    """              <p><span>Ferramentas</span>Flex + Bison</p>
              <p><span>Alvo</span>C</p>""",
    [
        ("estruturantes", "Estruturantes"),
        ("design", "Design"),
        ("codigo", "Decisões no código"),
        ("registro", "Como registrar"),
    ],
    sec("estruturantes", "00", "BASE", "Decisões estruturantes", """
            <div class="table-scroll">
              <table class="document-table">
                <thead><tr><th>Decisão</th><th>Alternativas</th><th>Justificativa</th></tr></thead>
                <tbody>
                  <tr><th>Compilador, não interpretador</th><td>Interpretar Python</td><td>Gera C compilável e cobre geração de código</td></tr>
                  <tr><th>Fonte: subset Python</th><td>Linguagem inventada / subset C</td><td>Sintaxe familiar e recorte controlável</td></tr>
                  <tr><th>Alvo C</th><td>Bytecode ou assembly</td><td>Validação fácil com GCC</td></tr>
                  <tr><th>Flex + Bison</th><td>Parser à mão</td><td>Exigência prática da disciplina</td></tr>
                  <tr><th>Scrum + site de docs</th><td>Kanban solto / só README</td><td>Atende sprints, decisões e problemas</td></tr>
                  <tr><th>Python → C (não JS)</th><td>Python → JavaScript (ata 2)</td><td>Alinha ao guia de compilador e ao GCC</td></tr>
                </tbody>
              </table>
            </div>
    """)
    + sec("registro", "01", "PROCESSO", "Como registrar novas decisões", """
            <ol class="numbered-list">
              <li>Contexto — o que motivou a escolha.</li>
              <li>Alternativas consideradas.</li>
              <li>Decisão adotada.</li>
              <li>Consequências em código, prazo ou testes.</li>
            </ol>
    """, last=True),
)

# ---------- PROBLEMAS ----------
page(
    "problemas.html",
    "Problemas e soluções",
    "Problemas encontrados e soluções no compilador.",
    "ACOMPANHAMENTO <span>/</span> IMPEDIMENTOS",
    "Problemas e <em>soluções</em>",
    "Problemas e soluções registrados nos formulários de ponto de controle P1 e P2.",
    """              <p><span>Fonte</span>lexer.l · parser.y · geracao.c</p>""",
    [
        ("p1", "Fase 1"),
        ("p2", "Fase 2"),
    ],
    sec("p1", "00", "FRONT-END", "Problemas e soluções 1", """
            <div class="table-scroll">
              <table class="document-table">
                <thead><tr><th>Problema</th><th>Solução</th></tr></thead>
                <tbody>
                  <tr><th>Ausência de padronização na arquitetura do repositório, que dificultava localizar arquivos e controlar versões.</th><td>Foi implementada uma nova estrutura de diretórios dedicados.</td></tr>
                </tbody>
              </table>
            </div>
    """)
    + sec("p2", "01", "BACKEND", "Problemas e soluções 2", """
            <div class="table-scroll">
              <table class="document-table">
                <thead><tr><th>Problema</th><th>Solução</th></tr></thead>
                <tbody>
                  <tr><th>Construção da árvore sintática (AST).</th><td>Dividir a implementação em etapas, validar cada estrutura com exemplos e revisar a integração com o parser.</td></tr>
                  <tr><th>Uso eficiente das ferramentas de inteligência artificial.</th><td>Usar as ferramentas como apoio, revisar as sugestões e validar o código antes de integrá-lo ao projeto.</td></tr>
                  <tr><th>Gestão do tempo.</th><td>Priorizar as tarefas, dividi-las entre os integrantes e acompanhar o progresso ao longo das sprints.</td></tr>
                </tbody>
              </table>
            </div>
    """, last=True),
)

page(
    "tokens.html",
    "Tokens",
    "Referência dos tokens reconhecidos pelo analisador léxico.",
    "REFERÊNCIA TÉCNICA <span>/</span> ANÁLISE LÉXICA",
    "Documentação dos <em>tokens</em>",
    "Referência alinhada a compilador/lexer/lexer.l e parser/parser.y do grupo G16 — não ao rascunho antigo de PRs pendentes.",
    """              <p><span>Lexer</span>Flex</p>
              <p><span>Parser</span>Bison</p>
              <p><span>Arquivo</span>lexer/lexer.l</p>""",
    [
        ("visao-geral", "Visão geral"),
        ("palavras-chave", "Palavras-chave"),
        ("operadores", "Operadores"),
        ("delimitadores", "Delimitadores"),
        ("literais", "Literais"),
        ("identificadores", "Identificadores"),
        ("indentacao", "Indentação"),
        ("comentarios", "Comentários"),
        ("invalidos", "Inválidos"),
        ("bison", "Bison"),
        ("resumo-tokens", "Resumo"),
    ],
    sec("visao-geral", "00", "FUNDAMENTOS", "O que são tokens?", """
            <p>O analisador léxico lê o código caractere a caractere e devolve tokens para o Bison. O wrapper <code>yylex</code> drena uma fila usada para INDENT/DEDENT.</p>
            <div class="code-block">
              <div class="code-block__header"><span>PYTHON</span><span>entrada</span></div>
              <pre><code>x = 10
print(x)</code></pre>
            </div>
            <div class="code-block">
              <div class="code-block__header"><span>TOKENS</span><span>simplificado</span></div>
              <pre><code>IDENTIFIER(x) ATRIBUES NUMBER(10) NEWLINE
PRINT LPAREN IDENTIFIER(x) RPAREN NEWLINE</code></pre>
            </div>
    """)
    + sec("palavras-chave", "01", "TOKENS", "Palavras-chave", """
            <div class="table-scroll">
              <table class="document-table">
                <thead><tr><th>Token</th><th>Padrão</th><th>Exemplo</th></tr></thead>
                <tbody>
                  <tr><th><code>PRINT</code></th><td><code>"print"</code></td><td><code>print(x)</code></td></tr>
                  <tr><th><code>IF</code></th><td><code>"if"</code></td><td><code>if n &gt; 4:</code></td></tr>
                  <tr><th><code>ELSE</code></th><td><code>"else"</code></td><td><code>else:</code></td></tr>
                  <tr><th><code>WHILE</code></th><td><code>"while"</code></td><td><code>while x &lt; 10:</code></td></tr>
                  <tr><th><code>DEF</code></th><td><code>"def"</code></td><td><code>def soma(a, b):</code></td></tr>
                  <tr><th><code>RETURN</code></th><td><code>"return"</code></td><td><code>return a + b</code></td></tr>
                </tbody>
              </table>
            </div>
            <div class="callout"><strong>Fora do escopo</strong><p><code>for</code>, <code>None</code>, <code>class</code> e <code>import</code> não são palavras-chave do lexer.</p></div>
    """)
    + sec("operadores", "02", "TOKENS", "Operadores", """
            <div class="table-scroll">
              <table class="document-table">
                <thead><tr><th>Token</th><th>Padrão</th><th>Uso</th></tr></thead>
                <tbody>
                  <tr><th><code>ATRIBUES</code></th><td><code>=</code></td><td>Atribuição</td></tr>
                  <tr><th><code>PLUS MINUS TIMES DIVIDE</code></th><td><code>+ - * /</code></td><td>Aritmética; <code>/</code> vira divisão real em C</td></tr>
                  <tr><th><code>EQ NEQ</code></th><td><code>== !=</code></td><td>Igualdade</td></tr>
                  <tr><th><code>LT GT LEQ GEQ</code></th><td><code>&lt; &gt; &lt;= &gt;=</code></td><td>Relacionais (nomes LEQ/GEQ no parser)</td></tr>
                </tbody>
              </table>
            </div>
            <p>Precedência Bison: relacionais abaixo de <code>+</code>/<code>-</code>, que ficam abaixo de <code>*</code>/<code>/</code>.</p>
    """)
    + sec("delimitadores", "03", "TOKENS", "Delimitadores", """
            <div class="table-scroll">
              <table class="document-table">
                <thead><tr><th>Token</th><th>Padrão</th><th>Papel</th></tr></thead>
                <tbody>
                  <tr><th><code>LPAREN</code> / <code>RPAREN</code></th><td><code>( )</code></td><td>Chamadas, print e agrupamento</td></tr>
                  <tr><th><code>COLON</code></th><td><code>:</code></td><td>Cabeçalho de if, while e def</td></tr>
                  <tr><th><code>COMMA</code></th><td><code>,</code></td><td>Parâmetros e argumentos</td></tr>
                  <tr><th><code>NEWLINE</code></th><td>quebra de linha</td><td>Termina comando e entra no estado BOL</td></tr>
                </tbody>
              </table>
            </div>
    """)
    + sec("literais", "04", "TOKENS", "Literais", """
            <div class="table-scroll">
              <table class="document-table">
                <thead><tr><th>Token</th><th>Padrão</th><th>Valor semântico</th></tr></thead>
                <tbody>
                  <tr><th><code>NUMBER</code></th><td><code>[0-9]+</code></td><td><code>yylval.inteiro</code></td></tr>
                  <tr><th><code>FLOAT</code></th><td><code>[0-9]+\\.[0-9]+</code></td><td><code>yylval.real</code></td></tr>
                  <tr><th><code>STRING</code></th><td>aspas simples ou duplas</td><td>lexema copiado, incluindo as aspas</td></tr>
                  <tr><th><code>BOOLEAN</code></th><td><code>True</code>/<code>False</code></td><td>1 ou 0 em <code>yylval.inteiro</code></td></tr>
                </tbody>
              </table>
            </div>
            <div class="callout"><strong>Compatibilidade</strong><p>Identificadores <code>true</code> e <code>false</code> ainda viram BOOLEAN. O padrão Python oficial é <code>True</code>/<code>False</code>.</p></div>
            <div class="callout callout--warning"><strong>Strings</strong><p>O lexer não trata escapes nem string não terminada com mensagem específica: aspas sem fechamento tendem a consumir o restante ou gerar caractere inválido.</p></div>
    """)
    + sec("identificadores", "05", "TOKENS", "Identificadores", """
            <p>Padrão <code>[a-zA-Z_][a-zA-Z0-9_]*</code>, depois das palavras-chave. O texto vai para <code>yylval.texto</code>.</p>
            <ul class="document-list">
              <li>Válidos: <code>x</code>, <code>soma</code>, <code>_var</code>.</li>
              <li>Inválidos: <code>1var</code>, <code>var-nome</code>.</li>
            </ul>
    """)
    + sec("indentacao", "06", "PYTHON", "INDENT, DEDENT e NEWLINE", """
            <p>No início de linha (estado <code>BOL</code>) o lexer mede espaços/tabs (tab = 4), compara com uma pilha e enfileira <code>INDENT</code> ou um ou mais <code>DEDENT</code>. Linhas vazias e comentários no BOL são ignorados. No EOF a indentação volta a zero.</p>
            <div class="callout callout--warning"><strong>Erros</strong><p>Indentação inconsistente ou profunda demais é reportada em stderr, com o número da linha.</p></div>
    """)
    + sec("comentarios", "07", "IGNORADOS", "Comentários e espaços", """
            <p>Comentários <code>#...</code> e espaços/tabs no meio da linha não geram token. <code>\\n</code> gera <code>NEWLINE</code> e volta ao estado BOL.</p>
    """)
    + sec("invalidos", "08", "ERROS", "Caracteres inválidos", """
            <p>A regra coringa imprime <code>Caractere invalido na linha N: ...</code> e continua, para reportar vários erros na mesma execução.</p>
    """)
    + sec("bison", "09", "INTEGRAÇÃO", "Integração com o Bison", """
            <p>Tokens declarados em <code>parser.y</code> com <code>%token</code>. Fluxo: Python → Flex → tokens → Bison → AST → semântica → <code>gerarCodigoC</code>.</p>
            <div class="code-block"><pre><code>%token PRINT IF ELSE WHILE DEF RETURN
%token COLON NEWLINE COMMA INDENT DEDENT
%token PLUS MINUS TIMES DIVIDE
%token EQ NEQ LEQ GEQ LT GT ATRIBUES</code></pre></div>
    """)
    + sec("resumo-tokens", "10", "REFERÊNCIA", "Resumo", """
            <div class="table-scroll">
              <table class="document-table">
                <thead><tr><th>Categoria</th><th>Tokens</th><th>Status</th></tr></thead>
                <tbody>
                  <tr><th>Keywords</th><td>PRINT IF ELSE WHILE DEF RETURN</td><td>No lexer</td></tr>
                  <tr><th>Aritmética</th><td>ATRIBUES PLUS MINUS TIMES DIVIDE</td><td>No lexer</td></tr>
                  <tr><th>Relacionais</th><td>EQ NEQ LT GT LEQ GEQ</td><td>No lexer</td></tr>
                  <tr><th>Estrutura</th><td>LPAREN RPAREN COLON COMMA NEWLINE INDENT DEDENT</td><td>No lexer</td></tr>
                  <tr><th>Literais</th><td>NUMBER FLOAT STRING BOOLEAN IDENTIFIER</td><td>No lexer</td></tr>
                  <tr><th>Fora do escopo</th><td>FOR NONE listas dicionários</td><td>Não implementado</td></tr>
                </tbody>
              </table>
            </div>
    """, last=True),
)

print("generated html")


