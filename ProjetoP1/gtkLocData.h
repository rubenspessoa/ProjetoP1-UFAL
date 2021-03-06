// VARIAVEIS GLOBAIS DO CADASTRO DE FILMES
extern const gchar *nome_filme;
extern const gchar *genero_filme;
extern const gchar *ano_filme;

// VARIAVEIS GLOBAIS DO CADASTRO DE EMPRESA

extern const gchar *entry_text_cadastro_empresa;
extern const gchar *entry_text_cadastro_usuario;
extern const gchar *entry_text_cadastro_senha;

//  VARIAVEIS GLOBAIS DA BUSCA POR FILMES
extern const gchar *entry_text_busca;
extern char busca [50];

// VARIAVEIS GLOBAIS DO LOGIN LOCDATA

extern const gchar *entry_text_login_usuario;
extern const gchar *entry_text_login_senha;
extern char usuario_login [30];
extern char senha_login [15];

extern char **argv;

void dialog_err_entry_vazio(GtkWidget *widget, GtkWidget *win);
void sobre_o_locdata (GtkWidget *wid, GtkWidget *win);
void dados_salvos (GtkWidget *wid, GtkWidget *win);
int callback(void *NotUsed, int argc, char **argv, char **azColName);
int callback_visualizar_dados(void *data, int argc, char **argv, char **azColName);
void enter_nome_filme (GtkWidget *widget, GtkWidget *entry);
void enter_genero_filme (GtkWidget *widget, GtkWidget *entry);
void enter_ano_filme (GtkWidget *widget, GtkWidget *entry);
void enter_cliente_cpf (GtkWidget *widget, GtkWidget *entry);
void enter_cliente_nome (GtkWidget *widget, GtkWidget *entry);
void enter_cliente_email (GtkWidget *widget, GtkWidget *entry);
void enter_cliente_endereco (GtkWidget *widget, GtkWidget *entry);
void enter_cliente_telefone (GtkWidget *widget, GtkWidget *entry);
void janela_cadastro_de_clientes ();
void janela_cadastro_de_filmes();
void enter_callback1 (GtkWidget *widget, GtkWidget *entry1);
void enter_callback2 (GtkWidget *widget, GtkWidget *entry2);
void enter_callback3 (GtkWidget *widget, GtkWidget *entry3);
void entry_toggle_visibility (GtkWidget *checkbutton, GtkWidget *entry);
void janela_cadastro_de_empresas();
void enter_callback_busca (GtkWidget *widget, GtkWidget *entry_busca);
void enter_callback4 (GtkWidget *widget, GtkWidget *entry1);
void enter_callback5 (GtkWidget *widget, GtkWidget *entry2);
void voltar_locacao (GtkWidget *wid, GtkWidget *win);
void locacao_confirmacao (GtkWidget *wid, GtkWidget *win);
void locacao ();
void devolucao_confirmacao ();
void devolucao ();
void janela_login();
void janela_principal();
