#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "cadastros.h"

// VARIAVEIS GLOBAIS DO CADASTRO DE FILMES
const gchar *nome_filme = NULL;
const gchar *genero_filme = NULL;
const gchar *ano_filme = NULL;

// VARIAVEIS GLOBAIS DO CADASTRO DE EMPRESA

const gchar *entry_text_cadastro_empresa = NULL;
const gchar *entry_text_cadastro_usuario = NULL;
const gchar *entry_text_cadastro_senha = NULL;

//  VARIAVEIS GLOBAIS DA BUSCA POR FILMES
const gchar *entry_text_busca = NULL;
char busca [50];

// VARIAVEIS GLOBAIS DO LOGIN LOCDATA

const gchar *entry_text_login_usuario = NULL;
const gchar *entry_text_login_senha = NULL;
char usuario_login [30];
char senha_login [15];

// FUNCOES AUXILIARES

void dialog_err_entry_vazio(GtkWidget *widget, GtkWidget *win) {

    GtkWidget *dialog = NULL;

    dialog = gtk_message_dialog_new (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "Por favor, preencha todos os campos.\n");
    gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
}

void sobre_o_locdata (GtkWidget *wid, GtkWidget *win) {
    GtkWidget *dialog = NULL;

    dialog = gtk_message_dialog_new (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "O LocData nasceu de uma necessidade: tornar a busca pelo seu filme predileto mais simples.\n\nPensando nisso, Eduardo Lúcio, Filipe Falcão, Gustavo Gobbi, Matheus Sales e Rubens Pessoa se encarregaram deste desafio como nosso projeto de Programação 1 orientado pelo professor Rodrigo Paes.\n\nEnjoy!\n");
    gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
}

// FUNCOES USADAS POR TODOS OS CADASTROS

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;

    for(i = 0; i < argc; i ++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");

    return 0;
}

int callback_visualizar_dados(void *data, int argc, char **argv, char **azColName) {
    int i;
    fprintf(stderr, "%s: ", (const char*)data);

    for(i = 0; i < argc; i ++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");

    return 0;
}

// FUNCOES GTK DO CADASTRO DE FILMES

static void enter_nome_filme (GtkWidget *widget, GtkWidget *entry) {

    nome_filme = gtk_entry_get_text(GTK_ENTRY(entry));
    printf ("Nome: %s\n", nome_filme);

}

static void enter_genero_filme (GtkWidget *widget, GtkWidget *entry) {

    genero_filme = gtk_entry_get_text (GTK_ENTRY(entry));
    printf ("Genero: %s\n", genero_filme);

}

static void enter_ano_filme (GtkWidget *widget, GtkWidget *entry) {

    ano_filme = gtk_entry_get_text (GTK_ENTRY(entry));
    printf ("Ano: %s\n", ano_filme);

}

void janela_cadastro_de_filmes() {
    GtkWidget *window, *vbox, *nomeEntry, *generoEntry, *anoEntry, *button, *fixed, *label;
    GtkEntryBuffer *nomeBuffer, *generoBuffer, *anoBuffer;
    gint tmp_pos;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW (window), GTK_WIN_POS_CENTER);
    gtk_widget_set_size_request(GTK_WIDGET (window), 400, 250);
    gtk_window_set_title(GTK_WINDOW (window), "Cadastro de Filmes");
    gtk_container_set_border_width(GTK_CONTAINER (window), 10);

    vbox = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (window), vbox);
    gtk_widget_show (vbox);

    label = gtk_label_new ("Insira abaixo o nome do filme.");
    gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_LEFT);
    gtk_box_pack_start (GTK_BOX (vbox), label, TRUE, TRUE, 0);

    nomeBuffer = gtk_entry_buffer_new("Ex.: Star Wars", 14);
    nomeEntry = gtk_entry_new_with_buffer(nomeBuffer);
    gtk_entry_set_max_length(GTK_ENTRY(nomeEntry), 100);
    g_signal_connect(nomeEntry, "changed", G_CALLBACK(enter_nome_filme), nomeEntry);
    tmp_pos = GTK_ENTRY(nomeEntry)->text_length;
    gtk_editable_select_region(GTK_EDITABLE(nomeEntry), 0, GTK_ENTRY(nomeEntry)->text_length);
    gtk_box_pack_start(GTK_BOX(vbox), nomeEntry, TRUE, TRUE, 0);
    gtk_widget_show(nomeEntry);

    label = gtk_label_new ("Insira abaixo o genero do filme.");
    gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_LEFT);
    gtk_box_pack_start (GTK_BOX (vbox), label, TRUE, TRUE, 0);

    generoBuffer = gtk_entry_buffer_new("Ex.: Acao", 9);
    generoEntry = gtk_entry_new_with_buffer(generoBuffer);
    gtk_entry_set_max_length(GTK_ENTRY(generoEntry), 100);
    g_signal_connect(generoEntry, "changed", G_CALLBACK(enter_genero_filme), generoEntry);
    tmp_pos = GTK_ENTRY(generoEntry)->text_length;
    gtk_editable_select_region(GTK_EDITABLE(generoEntry), 0, GTK_ENTRY(generoEntry)->text_length);
    gtk_box_pack_start(GTK_BOX(vbox), generoEntry, TRUE, TRUE, 0);
    gtk_widget_show(generoEntry);

    label = gtk_label_new ("Insira abaixo o ano do filme.");
    gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_LEFT);
    gtk_box_pack_start (GTK_BOX (vbox), label, TRUE, TRUE, 0);

    anoBuffer = gtk_entry_buffer_new("Ex.: 1998", 9);
    anoEntry = gtk_entry_new_with_buffer(anoBuffer);
    gtk_entry_set_max_length(GTK_ENTRY(anoEntry), 100);
    g_signal_connect(anoEntry, "changed", G_CALLBACK(enter_ano_filme), anoEntry);
    tmp_pos = GTK_ENTRY(anoEntry)->text_length;
    gtk_editable_select_region(GTK_EDITABLE(anoEntry), 0, GTK_ENTRY(anoEntry)->text_length);
    gtk_box_pack_start(GTK_BOX(vbox), anoEntry, TRUE, TRUE, 0);
    gtk_widget_show(anoEntry);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(vbox), fixed);
    gtk_widget_show (fixed);

    button = gtk_button_new_with_label ("Concluir");
    g_signal_connect (button, "clicked", G_CALLBACK (cadastro_de_filmes), window);
    gtk_fixed_put(GTK_FIXED(fixed), button, 230, 15);
    gtk_widget_set_size_request(button, 150, 35);
    gtk_widget_show(button);

    gtk_widget_show_all (window);
}

// FUNCOES GTK DO CADASTRO DE EMPRESAS

void enter_callback1 (GtkWidget *widget, GtkWidget *entry1) {

    entry_text_cadastro_empresa = gtk_entry_get_text (GTK_ENTRY (entry1));
    printf ("Empresa: %s\n", entry_text_cadastro_empresa);

}

void enter_callback2 (GtkWidget *widget, GtkWidget *entry2) {

    entry_text_cadastro_usuario = gtk_entry_get_text (GTK_ENTRY (entry2));
    printf ("Usuario: %s\n", entry_text_cadastro_usuario);

}

void enter_callback3 (GtkWidget *widget, GtkWidget *entry3) {

    entry_text_cadastro_senha = gtk_entry_get_text (GTK_ENTRY (entry3));
    printf ("Senha: %s\n", entry_text_cadastro_senha);

}

void entry_toggle_visibility (GtkWidget *checkbutton, GtkWidget *entry) {

  gtk_entry_set_visibility (GTK_ENTRY (entry), GTK_TOGGLE_BUTTON (checkbutton)->active);

}

void janela_cadastro_de_empresas () {

    GtkWidget *window;
    GtkWidget *vbox, *hbox;
    GtkWidget *entry1;
    GtkWidget *entry2;
    GtkWidget *entry3;
    GtkWidget *button;
    GtkWidget *check;
    GtkWidget *fixed;
    GtkWidget *label;
    gint tmp_pos;

    /*criando janela*/
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
    gtk_widget_set_size_request (GTK_WIDGET (window), 500, 300);
    gtk_window_set_title (GTK_WINDOW (window), "Registro de empresa LocData");
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    /*criando caixa vertical*/
    vbox = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (window), vbox);
    gtk_widget_show (vbox);

    label = gtk_label_new ("Insira abaixo o nome da sua empresa");
    gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_LEFT);
    gtk_box_pack_start (GTK_BOX (vbox), label, TRUE, TRUE, 0);

    /*criando três caixas de texto e três labels*/
    entry1 = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry1), 100);
    g_signal_connect (entry1, "changed", G_CALLBACK (enter_callback1), entry1);
    tmp_pos = GTK_ENTRY (entry1)->text_length;
    gtk_editable_select_region (GTK_EDITABLE (entry1), 0, GTK_ENTRY (entry1)->text_length);
    gtk_box_pack_start (GTK_BOX (vbox), entry1, TRUE, TRUE, 0);
    gtk_widget_show (entry1);

    label = gtk_label_new ("Insira abaixo o nome de usuário Admin");
    gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_LEFT);
    gtk_box_pack_start (GTK_BOX (vbox), label, TRUE, TRUE, 0);

    entry2 = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry2), 50);
    g_signal_connect (entry2, "changed", G_CALLBACK (enter_callback2), entry2);
    tmp_pos = GTK_ENTRY (entry2)->text_length;
    gtk_editable_select_region (GTK_EDITABLE (entry2), 0, GTK_ENTRY (entry2)->text_length);
    gtk_box_pack_start (GTK_BOX (vbox), entry2, TRUE, TRUE, 0);
    gtk_widget_show (entry2);

    label = gtk_label_new ("Insira abaixo a sua senha de usuário Admin");
    gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_LEFT);
    gtk_box_pack_start (GTK_BOX (vbox), label, TRUE, TRUE, 0);

    entry3 = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry3), 15);
    g_signal_connect (entry3, "changed", G_CALLBACK (enter_callback3), entry3);
    tmp_pos = GTK_ENTRY (entry3)->text_length;
    gtk_editable_select_region (GTK_EDITABLE (entry3), 0, GTK_ENTRY (entry3)->text_length);
    gtk_box_pack_start (GTK_BOX (vbox), entry3, TRUE, TRUE, 0);
    gtk_widget_show (entry3);

    /*criando um caixa vertical*/
    hbox = gtk_hbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (vbox), hbox);
    gtk_widget_show (hbox);

    /*criando um botão "toogle" de seleção*/
    check = gtk_check_button_new_with_label ("Visualizar senha");
    gtk_box_pack_start (GTK_BOX (hbox), check, TRUE, TRUE, 0);
    g_signal_connect (check, "toggled", G_CALLBACK (entry_toggle_visibility), entry3);
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (check), TRUE);
    gtk_widget_show (check);

    /*criando um widget fixed*/
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(vbox), fixed);
    gtk_widget_show (fixed);

    /*criando um botão de "salvar"*/
    button = gtk_button_new_with_label ("Salvar");
    g_signal_connect (button, "clicked", G_CALLBACK(cadastro_de_empresas), window);
    gtk_fixed_put(GTK_FIXED(fixed), button, 1, 15);
    gtk_widget_set_size_request(button, 150, 35);
    gtk_widget_show(button);

    /*mostrando todos os widgets dentro da janela*/
    gtk_widget_show_all (window);
}

// FUNCOES GTK DO CADASTRO DE CLIENTES

void janela_cadastro_de_clientes() {
}

// FUNCOES GTK DA BUSCA POR FILMES

void enter_callback_busca (GtkWidget *widget, GtkWidget *entry_busca) {

    entry_text_busca = gtk_entry_get_text (GTK_ENTRY (entry_busca));
    printf ("Buscando: %s\n", entry_text_busca);

}

// FUNCOES GTK DO LOGIN

void enter_callback4 (GtkWidget *widget, GtkWidget *entry1) {

    entry_text_login_usuario = gtk_entry_get_text (GTK_ENTRY (entry1));
    printf ("Usuario: %s\n", entry_text_login_usuario);

}

void enter_callback5 (GtkWidget *widget, GtkWidget *entry2) {

    entry_text_login_senha = gtk_entry_get_text (GTK_ENTRY (entry2));
    printf ("Senha: %s\n", entry_text_login_senha);

}

// FUNCAO DA JANELA PRINCIPAL

void janela_principal () {
    GtkWidget *window = NULL;
    GtkWidget *hbox;
    GtkWidget *vbox, *vbox2, *vbox3;
    GtkWidget *frame;
    GtkWidget *label;
    GtkWidget *button;
    GtkWidget *fixed;
    GtkWidget *entry_busca;
    gint tmp_pos;

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Pesquisa");
    gtk_widget_set_size_request (GTK_WIDGET (window), 600, 310);
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);

    vbox = gtk_vbox_new (FALSE, 5);

    hbox = gtk_hbox_new (FALSE, 5);
    gtk_container_add (GTK_CONTAINER (window), hbox);
    gtk_box_pack_start (GTK_BOX (hbox), vbox, FALSE, FALSE, 0);
    gtk_container_set_border_width (GTK_CONTAINER (window), 5);

    frame = gtk_frame_new ("Administrador");
    gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 0);

    vbox2 = gtk_vbox_new (FALSE, 15);
    gtk_container_add (GTK_CONTAINER (frame), vbox2);

    label = gtk_label_new ("\n  Registre filmes e clientes, efetue \n  locações e devoluções!  ");
    gtk_container_add (GTK_CONTAINER (vbox2), label);

    fixed = gtk_fixed_new ();
    gtk_container_add (GTK_CONTAINER(vbox2), fixed);

    button = gtk_button_new_with_label ("Locação");
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (janela_cadastro_de_empresas), (gpointer) window);
    gtk_fixed_put (GTK_FIXED (fixed), button, 10, 17);
    gtk_widget_set_size_request (button, 200, 42);

    button = gtk_button_new_with_label ("Devolução");
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (janela_cadastro_de_empresas), (gpointer) window);
    gtk_fixed_put (GTK_FIXED (fixed), button, 10, 77);
    gtk_widget_set_size_request (button, 200, 42);

    button = gtk_button_new_with_label ("Cadastros");
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (janela_cadastro_de_filmes), (gpointer) window);
    gtk_fixed_put (GTK_FIXED (fixed), button, 10, 137);
    gtk_widget_set_size_request (button, 200, 42);

    label = gtk_label_new ("");
    gtk_container_add (GTK_CONTAINER (vbox2), label);

    vbox = gtk_vbox_new (FALSE, 25);
    gtk_box_pack_start (GTK_BOX (hbox), vbox, FALSE, FALSE, 0);
    frame = gtk_frame_new ("Pesquisa");
    gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 0);

    vbox2 = gtk_vbox_new (FALSE, 15);
    gtk_container_add (GTK_CONTAINER (frame), vbox2);

    label = gtk_label_new ("\n  Encontre aqui de maneira rápida e precisa o que \n  você busca!  \n");
    gtk_container_add (GTK_CONTAINER (vbox2), label);

    entry_busca = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry_busca), 100);
    g_signal_connect (entry_busca, "changed", G_CALLBACK (enter_callback_busca), entry_busca);
    tmp_pos = GTK_ENTRY (entry_busca)->text_length;
    gtk_editable_select_region (GTK_EDITABLE (entry_busca), 0, GTK_ENTRY (entry_busca)->text_length);
    gtk_box_pack_start (GTK_BOX (vbox2), entry_busca, TRUE, TRUE, 0);
    gtk_widget_show (entry_busca);

    label = gtk_label_new ("\n\n\n\n\n\n\n\n");
    gtk_container_add (GTK_CONTAINER (vbox2), label);

    gtk_widget_show_all (window);

}

void janela_login () {
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *fixed;
    GtkWidget *button;
    GtkWidget *label;
    GtkWidget *entry1, *entry2;
    gint tmp_pos;

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
    gtk_widget_set_size_request (GTK_WIDGET (window), 280, 210);
    gtk_window_set_title (GTK_WINDOW (window), "Login de Admin LocData");
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    vbox = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (window), vbox);
    gtk_widget_show (vbox);

    label = gtk_label_new ("Usuário:");
    gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_LEFT);
    gtk_box_pack_start (GTK_BOX (vbox), label, TRUE, TRUE, 0);

    entry1 = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry1), 100);
    g_signal_connect (entry1, "changed", G_CALLBACK (enter_callback4), entry1);
    tmp_pos = GTK_ENTRY (entry1)->text_length;
    gtk_editable_select_region (GTK_EDITABLE (entry1), 0, GTK_ENTRY (entry1)->text_length);
    gtk_box_pack_start (GTK_BOX (vbox), entry1, TRUE, TRUE, 0);
    gtk_widget_show (entry1);

    label = gtk_label_new ("Senha:");
    gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_LEFT);
    gtk_box_pack_start (GTK_BOX (vbox), label, TRUE, TRUE, 0);

    entry2 = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry2), 50);
    g_signal_connect (entry2, "changed", G_CALLBACK (enter_callback5), entry2);
    tmp_pos = GTK_ENTRY (entry2)->text_length;
    gtk_editable_select_region (GTK_EDITABLE (entry2), 0, GTK_ENTRY (entry2)->text_length);
    gtk_box_pack_start (GTK_BOX (vbox), entry2, TRUE, TRUE, 0);
    gtk_widget_show (entry2);

    fixed = gtk_fixed_new ();
    gtk_container_add (GTK_CONTAINER (vbox), fixed);

    button = gtk_button_new_with_label ("Entrar");
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (janela_principal), (gpointer) window);
    gtk_fixed_put (GTK_FIXED (fixed), button, 160, 10);
    gtk_widget_set_size_request (button, 100, 35);

    gtk_widget_show_all (window);
}


