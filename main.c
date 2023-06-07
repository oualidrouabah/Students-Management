//  !! USE gcc compiler !!

// ----------------------
// 6 semestres Licence
// 4 semestres Master

//  - Chaque semestre contient des modules defirent
//  - Chaque module contient : note CC , note exament et Moyenne

// Proposer un programme en C permet de gerer un listeinfinie d'etudiants.
//  Chaque etudiant est represente par : un matricule, Nom , Prenom , Date de naissance,
//  date inscription, les modules leurs notes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define bool int
#define true 1
#define false 0

#define null NULL
#define numberOfSemesters 10

#define dont_change -1
#define dont_use -404
#define numeric_null -999

#define horizontal_line "===========================================================\n"
#define thickhorizontal_line "-----------------------------------------------------------\n"

// COLORS
#define FgReset "\x1b[0m"
#define FgRed "\x1b[31m"
#define FgYellow "\x1b[33m"
#define FgBlue "\x1b[34m"
#define FgGreen "\x1b[32m"
#define FgCyan "\x1b[36m"
#define FgBlack "\x1b[30m"

#define BgCyan "\x1b[46m"
#define BgBlack "\x1b[40m"

double total_etudiant = 0;

enum Level
{
    Licence,
    Master
};

struct Semestre
{
    enum Level level;
    int number_of_semestre;

    // using linked list
    // for infinity module and etudiant
    struct Module *list_modules;
    struct Etudiant *list_etudiant;
};
typedef struct Semestre sm;

struct Module
{
    char module_name[25];
    int factor;
    double td;
    double tp;
    double examn;
    double moyenne;
    // using linked list
    // for infinity module
    struct Module *next_module;
};
typedef struct Module modl;

struct Etudiant
{
    double matricule;
    char first_name[25];
    char second_name[25];
    struct Date *date_of_birth;
    struct Date *registration_date;
    struct Module *list_modules_etudiant;
    double moyenne_generale;
    // using linked list
    // for infinity etudiants
    struct Etudiant *next_etudiant;
};
typedef struct Etudiant etd;

struct Date
{
    int day, month, year;
};
typedef struct Date date;

// dashboard functions
void init();

void dashboard(sm *list_of_semesters[numberOfSemesters]);

void main_commands(sm *list_of_semesters[numberOfSemesters]);
void showMainCommands();
void semestre_commands(sm *semestre_commands);
void etudiant_commands(etd *etudiant);
void module_commands(modl *module, etd *etudiant);

void showSemestreCommands(int number_of_semester);
void showEtudiantCommands(etd *etudiant);
void showModuleCommands(modl *module, etd *etudiant);

void selectSemester(sm *list_of_semestre[]);
void selectEtudiant(sm *semester);
void selectModule(etd *etudiant);

// utils
void clear_screen();
void exit_dashboard();
void back_message();
modl *copy_list_of_modules(modl *list_of_modules);
void nicePrint(char startColor[], char text1[], char mdColor[], char text2[], char endColor[]);
void insertNote(modl *module, char text[], int type);
int getNumber(int from, int to);

void randomGenrateNotesForAllSemester(sm *list_of_semesters[numberOfSemesters]);
void randomGenrateNotesForSemester(sm *semester);
void randomGenrateNotesForEtudiant(etd *etudiant);

// Semestre functions
sm *createSemestre(enum Level lvl, int number_of_semestre);
void showSemestreEtudiant(sm *semestre);
void showSemestreModules(sm *semestre);
void showAllSemestres(sm *list_of_semesters[numberOfSemesters], bool decorate);

// Etudiant functions
etd *createEtudiant(char fName[], char sName[], date *birth_date);
etd *manualCreateEtudiant();
void addEtudiantTo(etd *etudian, sm *semestre);
void displayEtudiantInfo(etd *etudiant, bool advanceShow, bool vertical);
void SearchForEtudiant(etd *etudiant);
void AdvanceSearchForEtudiant(etd *etudiant);
int CountEtudiantsForSemester(sm *semestre);
int CountAllEtudiants(sm *list_of_semestres[numberOfSemesters]);
void showEtudiantForSemester(sm *semestre, bool decorate);
void ShowAllEtudiant(sm *list_of_semestres[numberOfSemesters]);
etd *getEtudiantByIndex(sm *semester, int index);
void createAndAddEtudiantTo(sm *semestre);

double calcMoyenForEtudiant(etd *etudiant);
void calcMoyenForAllEtudiant(sm *list_of_semestres[numberOfSemesters]);
void calcMoyenForAllEtudiantOfSemester(sm *semester);

void showEtudiantsAdminsForAllSemesters(sm *list_semester[numberOfSemesters]);
void showEtudiantsAdminsForSemester(sm *semester);
bool isEtudiantAdmin(etd *etudiant);

// Module funtions
void createAndADDModuleTo(sm *semester);
modl *createModule(char module_name[25], int factor, bool use_tp);
void manualEditModule(modl *module, bool all_options);
void editModule(modl *module, char module_name[25], int factor, double tp, double td, double examn, double moyenne);
void displayModuletInfo(modl *module, bool allInfo);
double calcModuleMoyen(modl *module);
void showEtudiantModules(etd *etudiant, bool allInfo);
modl *getModuleByIndex(etd *etudiant, int index);
void restModule(modl *module);

void addModuletTo(modl *module, sm *semestre);
void addModuleToSemesterEtudiants(modl *module, etd *etudiant_list);
void addModuleToEtudiant(modl *module, etd *etudiant);

void showAllModuleForSemester(sm *semester);
void showAllModule(sm *list_semester[numberOfSemesters]);
// Date functions
date *createDate(int day, int month, int year);
bool validateDay(int day);
bool validateYear(int month);
bool validateMonth(int year);
date *getTodayDate();

// new functions

void showStatisticsForAllSomester(sm *list_semester[numberOfSemesters], int type);
void showStatisticsForSomester(sm *semester);
void printPercentage(int number, bool addBars);
void countEtudiantStateByAllSomester(sm *list_semester[numberOfSemesters], int *admins, int *ajournes, int *notCalc);
void countEtudiantStateBySomester(sm *semester, int *admins, int *ajournes, int *notCalc);
void countEtudiantByState(etd *etudiant, int *admins, int *ajournes, int *notCalc);

// MAIN ===========================================================================================
int main(int argc, char const *argv[])
{
    srand(time(NULL));
    init();

    return EXIT_SUCCESS;
}
// =================================================================================================

// dashboard functions =========================================================

void dashboard(sm *list_of_semesters[numberOfSemesters])
{
    main_commands(list_of_semesters);
}

void main_commands(sm *list_of_semesters[numberOfSemesters])
{

    bool stay_in_loop = true;
    int options_selected = 0;
    while (stay_in_loop)
    {

        showMainCommands();
        switch (options_selected)
        {
        case 1:
            clear_screen();
            showAllSemestres(list_of_semesters, true);
            back_message();
            getchar();
            getchar();
            break;
        case 2:
            clear_screen();
            selectSemester(list_of_semesters);

            break;
        case 3:
            clear_screen();
            ShowAllEtudiant(list_of_semesters);
            back_message();
            getchar();
            getchar();
            break;

        case 4:
            clear_screen();
            showAllModule(list_of_semesters);
            back_message();
            getchar();
            getchar();
            break;

        case 5:
            clear_screen();
            showEtudiantsAdminsForAllSemesters(list_of_semesters);
            back_message();
            getchar();
            getchar();
            break;
        case 6:
            clear_screen();
            showStatisticsForAllSomester(list_of_semesters, 1);
            back_message();
            getchar();
            getchar();
            break;
        case 7:
            clear_screen();
            showStatisticsForAllSomester(list_of_semesters, 2);
            back_message();
            getchar();
            getchar();
            break;
        case 8:
            clear_screen();
            showStatisticsForAllSomester(list_of_semesters, 3);
            back_message();
            getchar();
            getchar();
            break;
        case 9:
            clear_screen();
            nicePrint(FgGreen, horizontal_line, FgReset, null, null);
            printf("All Statistics For All Semesters \n");
            nicePrint(FgGreen, horizontal_line, FgReset, null, null);
            showStatisticsForAllSomester(list_of_semesters, 0);
            printf("\n\n\n\n\n\n\n\n");
            for (int i = 0; i < numberOfSemesters; i++)
            {
                showStatisticsForSomester(list_of_semesters[i]);
            }

            back_message();
            getchar();
            getchar();
            break;
        case 10:
            clear_screen();
            printf("le nombre des etudiants inscrits est ");
            nicePrint(FgGreen, null, null, null, null);
            printf("%.0lf \n", total_etudiant);
            nicePrint(FgReset, null, null, null, null);
            back_message();
            getchar();
            getchar();
            break;
        case 11:
            clear_screen();
            calcMoyenForAllEtudiant(list_of_semesters);
            printf("Done !/n");
            back_message();
            getchar();
            getchar();
            break;
        case 12:
            exit_dashboard();
            break;
        }
        if (options_selected == 0)
        {
            printf("\n select option : ");
            scanf("%d", &options_selected);
        }
        else
            options_selected = 0;
    }
}

void showMainCommands()
{
    clear_screen();

    nicePrint(FgGreen, horizontal_line, FgReset, null, null);
    nicePrint("  Main options  ", "\n", null, null, null);
    nicePrint(FgGreen, horizontal_line, FgReset, null, null);
    nicePrint(FgYellow, " 1", FgReset, " Show all semester\n", null);
    nicePrint(FgYellow, " 2", FgReset, " Select Semester \n", null);
    nicePrint(FgYellow, " 3", FgReset, " Show all Etudiant \n", null);
    nicePrint(FgYellow, " 4", FgReset, " Show all modules \n", null);
    nicePrint(FgYellow, " 5", FgReset, " Afficher les etudiants dont la moyennes >=10  \n", null);
    nicePrint(FgYellow, " 6", FgReset, " Afficher % des Etudiants dont la moyennes >=10(admins)  \n", null);
    nicePrint(FgYellow, " 7", FgReset, " Afficher % des Etudiants dont la moyennes <10(ajournes)  \n", null);
    nicePrint(FgYellow, " 8", FgReset, " Afficher % des Etudiants dont la moyennes not calculated yet  \n", null);
    nicePrint(FgYellow, " 9", FgReset, " Afficher all statistics  \n", null);
    nicePrint(FgYellow, " 10", FgReset, " Afficher le nombre des etudiants inscrits  \n", null);
    nicePrint(FgYellow, " 11", FgReset, " clc moyennes for all etudiants \n", null);
    nicePrint(FgGreen, horizontal_line, FgReset, null, null);
    nicePrint(FgYellow, " 12", FgReset, " Exit\n", null);
}

void semestre_commands(sm *semestre)
{
    bool stay_in_loop = true;
    int options_selected = -1;
    while (stay_in_loop)
    {

        showSemestreCommands(semestre->number_of_semestre);
        switch (options_selected)
        {
        case 1:
            clear_screen();
            showSemestreEtudiant(semestre);
            back_message();
            getchar();
            getchar();
            break;
        case 2:
            clear_screen();
            selectEtudiant(semestre);
            break;
        case 3:
            clear_screen();
            showSemestreModules(semestre);
            back_message();
            getchar();
            getchar();
            break;

        case 4:
            clear_screen();
            createAndAddEtudiantTo(semestre);
            back_message();
            getchar();
            getchar();
            break;
        case 5:
            clear_screen();
            createAndADDModuleTo(semestre);
            back_message();
            getchar();
            getchar();
            break;
        case 0:
            stay_in_loop = false;
            break;
        }

        if (options_selected == -1)
        {
            printf("\n select option : ");
            scanf("%d", &options_selected);
        }
        else
            options_selected = -1;
    }
}

void showSemestreCommands(int number_of_semester)
{
    char temp[5];
    // convert int to string
    sprintf(temp, "S%d", number_of_semester);

    clear_screen();
    nicePrint(FgGreen, horizontal_line, FgReset, null, null);
    nicePrint("All options  for [Semester ", FgCyan, temp, FgReset, "]\n");
    nicePrint(FgGreen, horizontal_line, FgReset, null, null);
    nicePrint(FgYellow, "1 ", FgReset, "Show students semester\n", null);
    nicePrint(FgYellow, "2 ", FgReset, "Select students semester\n", null);
    nicePrint(FgYellow, "3 ", FgReset, "Show modules semester \n", null);
    nicePrint(FgYellow, "4 ", FgReset, "Add student \n", null);
    nicePrint(FgYellow, "5 ", FgReset, "Add module \n", null);
    nicePrint(FgGreen, horizontal_line, FgReset, null, null);

    printf("\n0 Go Back \n");
}

void etudiant_commands(etd *etudiant)
{
    bool stay_in_loop = true;
    int options_selected = -1;

    while (stay_in_loop)
    {

        showEtudiantCommands(etudiant);
        switch (options_selected)
        {
        case 1:
            clear_screen();
            displayEtudiantInfo(etudiant, true, true);
            back_message();
            getchar();
            getchar();
            break;
        case 2:
            clear_screen();
            showEtudiantModules(etudiant, true);
            back_message();
            getchar();
            getchar();
            break;
        case 3:
            clear_screen();
            selectModule(etudiant);
            break;

        case 4:
            clear_screen();

            if (calcMoyenForEtudiant(etudiant) != numeric_null)
            {
                printf("Done !");
                printf("moyenne general %.2lf \n", etudiant->moyenne_generale);
            }
            else
            {
                printf("some notes are messing \n");
            }

            back_message();
            getchar();
            getchar();
            break;
        case 5:
            clear_screen();
            if (etudiant->moyenne_generale != numeric_null)
            {
                printf("moyenne general %.2lf \n", etudiant->moyenne_generale);
            }
            else
            {
                printf("moyenne general is not calculated yet \n");
            }
            back_message();
            getchar();
            getchar();
            break;

        case 0:
            stay_in_loop = false;
            break;
        }

        if (options_selected == -1)
        {
            printf("\n select option : ");
            scanf("%d", &options_selected);
        }
        else
            options_selected = -1;
    }
}

void showEtudiantCommands(etd *etudiant)
{
    clear_screen();

    nicePrint(FgGreen, horizontal_line, FgReset, null, null);

    printf(" All options for etudiant %.0lf %s %s \n", etudiant->matricule, etudiant->first_name, etudiant->second_name);
    nicePrint(FgGreen, horizontal_line, FgReset, null, null);
    nicePrint(FgYellow, "1 ", FgReset, "Show student info\n", null);
    nicePrint(FgYellow, "2 ", FgReset, "Show all module \n", null);
    nicePrint(FgYellow, "3 ", FgReset, "Select module \n", null);
    nicePrint(FgYellow, "4 ", FgReset, "calc moyenne genral \n", null);
    nicePrint(FgYellow, "5 ", FgReset, "Show moyenne genral \n", null);
    nicePrint(FgGreen, horizontal_line, FgReset, null, null);

    printf("\n0 Go Back \n");
}

void module_commands(modl *module, etd *etudiant)
{
    bool stay_in_loop = true;
    int options_selected = -1;

    while (stay_in_loop)
    {

        showModuleCommands(module, etudiant);
        switch (options_selected)
        {
        case 1:
            clear_screen();
            displayModuletInfo(module, true);
            back_message();
            getchar();
            getchar();
            break;
        case 2:
            clear_screen();
            // TODO: implement this function
            // printf("edit module  is not emplimented\n");
            manualEditModule(module, false);
            back_message();
            getchar();
            getchar();
            break;
        case 3:
            clear_screen();
            // TODO: implement this function
            if (module->moyenne != numeric_null)
            {
                printf("module moyenne is : %.2lf\n", module->moyenne);
            }
            else
            {

                printf("module moyenne not calculated yet\n");
            }
            back_message();
            getchar();
            getchar();
            break;
        case 4:
            clear_screen();
            if (calcModuleMoyen(module) == numeric_null)
            {
                printf("some note are messing \n");
            }
            else
            {
                printf("Done !\n");
                printf("moyenne : %.2lf\n", module->moyenne);
            };
            back_message();
            getchar();
            getchar();
            break;

        case 5:
            clear_screen();
            restModule(module);
            printf("Done !\n");
            back_message();
            getchar();
            getchar();
            break;

        case 0:
            stay_in_loop = false;
            break;
        }

        if (options_selected == -1)
        {
            printf("\n select option : ");
            scanf("%d", &options_selected);
        }
        else
            options_selected = -1;
    }
}

void showModuleCommands(modl *module, etd *etudiant)
{
    clear_screen();

    nicePrint(FgGreen, horizontal_line, FgReset, null, null);
    printf(" All options for Module %s  of Etudiant %.0lf %s %s \n", module->module_name, etudiant->matricule, etudiant->first_name, etudiant->second_name);
    nicePrint(FgGreen, horizontal_line, FgReset, null, null);
    nicePrint(FgYellow, "1 ", FgReset, "Show module info\n", null);
    nicePrint(FgYellow, "2 ", FgReset, "Edit module \n", null);
    nicePrint(FgYellow, "3 ", FgReset, "Show module moyenne \n", null);
    nicePrint(FgYellow, "4 ", FgReset, "clc module moyenne \n", null);
    nicePrint(FgYellow, "5 ", FgReset, "Rest module \n", null);
    nicePrint(FgGreen, horizontal_line, FgReset, null, null);

    printf("\n0 Go Back \n");
}

void selectSemester(sm *list_of_semestre[])
{
    int option = -1;
    bool stay_in_loop = true;
    while (stay_in_loop)
    {
        clear_screen();
        showAllSemestres(list_of_semestre, false);
        printf("\n0 \t Go back\n");
        printf("\n select option : ");
        scanf("%d", &option);

        if (option > 0 && option < 11)
            semestre_commands(list_of_semestre[option - 1]);

        if (option == 0)
            stay_in_loop = false;
    }
}

void selectEtudiant(sm *semester)
{
    int option = -1;
    bool stay_in_loop = true;
    while (stay_in_loop)
    {
        clear_screen();
        showEtudiantForSemester(semester, false);
        printf("\n0 \t Go back\n");
        printf("\n select option : ");
        scanf("%d", &option);

        // if (option > 0 && option < 11)
        //     etudiant_commands(list_of_semestre[option-1]);

        if (option == 0)
            stay_in_loop = false;
        else
        {
            etd *temp_etudiant = getEtudiantByIndex(semester, option);
            if (temp_etudiant != null)
            {
                etudiant_commands(temp_etudiant);
            }
        }
    }
}

void selectModule(etd *etudiant)
{
    int option = -1;
    bool stay_in_loop = true;
    while (stay_in_loop)
    {
        clear_screen();
        showEtudiantModules(etudiant, false);
        printf("\n0 \t Go back\n");

        printf("\n select option : ");
        scanf("%d", &option);

        if (option == 0)
            stay_in_loop = false;
        else
        {
            modl *temp_module = getModuleByIndex(etudiant, option);
            if (temp_module != null)
            {
                module_commands(temp_module, etudiant);
            }
        }
    }
}

// utils functions =========================================================

void clear_screen()
{
    system("clear");
}

void exit_dashboard()
{
    clear_screen();
    printf("\n Good bye !! \n");
    exit(EXIT_SUCCESS);
}

void back_message()
{
    printf("\npress enter to go back\n");
}

modl *copy_list_of_modules(modl *list_of_modules)
{
    if (list_of_modules == null)
        return null;

    modl *copy_list_module;

    if (list_of_modules->tp == dont_use)
        copy_list_module = createModule(list_of_modules->module_name, list_of_modules->factor, false);
    else
        copy_list_module = createModule(list_of_modules->module_name, list_of_modules->factor, true);

    modl *copy_last_node = copy_list_module;

    modl *temp_module = list_of_modules->next_module;

    while (temp_module != null)
    {
        if (temp_module->tp == dont_use)
            copy_last_node->next_module = createModule(temp_module->module_name, list_of_modules->factor, false);
        else
            copy_last_node->next_module = createModule(temp_module->module_name, list_of_modules->factor, true);

        // copy_last_node->next_module = createModule(temp_module->module_name);
        copy_last_node = copy_last_node->next_module;

        temp_module = temp_module->next_module;
    }

    copy_last_node->next_module = null;

    return copy_list_module;
}

void nicePrint(char startColor[], char text1[], char mdColor[], char text2[], char endColor[])
{
    if (startColor != null)
        printf("%s", startColor);

    if (text1 != null)
        printf("%s", text1);

    if (mdColor != null)
        printf("%s", mdColor);

    if (text2 != null)
        printf("%s", text2);

    if (endColor != null)
        printf("%s", endColor);
}

void insertNote(modl *module, char text[], int type)
{
    double temp_note;
    while (true)
    {
        clear_screen();
        if (text != null)
            printf("%s", text);
        scanf("%lf", &temp_note);
        if (temp_note >= 0 && temp_note <= 20)
        {
            if (type == 1)
            {
                module->factor = (int)temp_note;
                return;
            }
            else if (type == 2)
            {
                module->tp = temp_note;
                return;
            }
            else if (type == 3)
            {
                module->td = temp_note;
                return;
            }
            else if (type == 4)
            {
                module->examn = temp_note;
                return;
            }
            else
            {
                printf("type error in [ insertNote ] exit");
                exit(EXIT_FAILURE);
            }
        }
    }
}

int getNumber(int from, int to)
{
    // srand(time(NULL));
    int r = rand();
    int count = 0;
    while (r < from || r > to)
    {
        if (count > 5)
        {
            if (r % 10 >= from && r % 10 <= to)
                return r % 10;
            if (r % 100 >= from && r % 100 <= to)
                return r % 100;
            if (r % 1000 >= from && r % 1000 <= to)
                return r % 1000;
            if (r % 10000 >= from && r % 10000 <= to)
                return r % 10000;
            if (r % 100000 >= from && r % 100000 <= to)
                return r % 100000;
            if (r % 1000000 >= from && r % 1000000 <= to)
                return r % 1000000;
        }

        r = rand();
        count++;
    }

    return r;
}

// Semestre functions =========================================================

sm *createSemestre(enum Level lvl, int number_of_semestre)
{
    sm *smstr = (sm *)malloc(sizeof(sm));
    smstr->level = lvl;
    smstr->number_of_semestre = number_of_semestre;
    smstr->list_etudiant = null;
    smstr->list_modules = null;

    return smstr;
}

void showSemestreEtudiant(sm *semestre)
{
    showEtudiantForSemester(semestre, true);
}

void showSemestreModules(sm *semestre)
{
    if (semestre->list_modules == null)
    {
        nicePrint(FgYellow, "no module in this semestre \n", FgReset, null, null);
        // printf("no module in this semestre \n");
        return;
    }

    modl *list_modules = semestre->list_modules;
    printf("Modules:[");
    while (list_modules != null)
    {
        printf(" %s,", list_modules->module_name);
        list_modules = list_modules->next_module;
    }
    printf("]\n");
    // free(list_modules);
}

void showAllSemestres(sm *list_of_semesters[numberOfSemesters], bool decorate)
{
    if (list_of_semesters == null)
        return;
    printf("Semesters :\n");

    if (decorate)
        printf("[ \n");

    for (int i = 0; i < numberOfSemesters; i++)
    {
        if (decorate == false)
        {
            char temp[5];
            sprintf(temp, "%d", i + 1);
            nicePrint(FgYellow, temp, FgReset, null, null);
        }
        // printf("%d ", i + 1);

        // printf("\t S%d level ", list_of_semesters[i]->number_of_semestre);

        char temp_2[255];
        sprintf(temp_2, "\t S%d", list_of_semesters[i]->number_of_semestre);
        nicePrint(FgCyan, temp_2, FgReset, " level ", null);
        if (list_of_semesters[i]->level == Licence)
            // printf("Licence \n");
            nicePrint(FgCyan, "Licence \n", FgReset, null, null);
        else
            nicePrint(FgCyan, "Master \n", FgReset, null, null);
        // printf("Master \n");
    }

    if (decorate)
        printf("] \n");
}

// Etudiant Functions =========================================================

etd *createEtudiant(char fName[25], char sName[25], date *birth_date)
{
    etd *etudiant = (etd *)malloc(sizeof(etd));

    if (fName == null)
    {
        printf("insert first name: ");
        scanf("%s", etudiant->first_name);
    }
    else
    {
        strcpy(etudiant->first_name, fName);
    }

    if (sName == null)
    {
        printf("insert second name: ");
        scanf("%s", etudiant->second_name);
    }
    else
    {
        strcpy(etudiant->second_name, sName);
    }

    if (birth_date == null)
    {
        getchar();
        getchar();
        printf("insert birth day\n");
        etudiant->date_of_birth = createDate(-1, -1, -1);
    }
    else
    {
        etudiant->date_of_birth = birth_date;
    }

    etudiant->matricule = numeric_null;
    etudiant->moyenne_generale = numeric_null;
    etudiant->list_modules_etudiant = null;
    etudiant->next_etudiant = null;

    return etudiant;
}

void createAndAddEtudiantTo(sm *semestre)
{
    // TODO: i removed pointer from new_etudiant
    etd *new_etudiant = manualCreateEtudiant();
    addEtudiantTo(new_etudiant, semestre);
}

etd *manualCreateEtudiant()
{
    etd *new_etudiant = createEtudiant(null, null, null);
    return new_etudiant;
}

void addEtudiantTo(etd *etudian, sm *semestre)
{
    if (etudian == null)
        return;

    if (semestre->list_etudiant == null)
    {
        total_etudiant++;

        semestre->list_etudiant = etudian;
        etudian->matricule = total_etudiant;

        etudian->list_modules_etudiant = copy_list_of_modules(semestre->list_modules);
        etudian->registration_date = getTodayDate();
        return;
    }

    etd *temp_etd = semestre->list_etudiant;

    while (temp_etd->next_etudiant != null)
    {
        temp_etd = temp_etd->next_etudiant;
    }

    total_etudiant++;
    temp_etd->next_etudiant = etudian;
    etudian->matricule = total_etudiant;

    // TODO: copy list_of_modules
    etudian->list_modules_etudiant = copy_list_of_modules(semestre->list_modules);
    etudian->registration_date = getTodayDate();
}

void displayEtudiantInfo(etd *etudiant, bool advanceShow, bool vertical)
{
    if (vertical == true)
    {
        printf("\n");
        printf("matricule :\t\t");
    }

    if (etudiant->matricule == numeric_null)
        printf("undfined");
    else
        printf("%.0lf\t", etudiant->matricule);

    if (vertical == true)
    {
        printf("\n");
        printf("fisrt name:\t\t");
    }
    printf("%s \t\t", etudiant->first_name);

    if (vertical == true)
    {
        printf("\n");
        printf("second name:\t\t");
    }

    printf("%s \t", etudiant->second_name);

    if (vertical == true)
    {
        printf("\n");
        printf("moyenne generale :\t");
    }

    if (etudiant->moyenne_generale == numeric_null)
        printf("not calculated\t");
    else
        printf(" %.2lf\t", etudiant->moyenne_generale);

    if (advanceShow)
    {
        if (etudiant->date_of_birth != null)
        {

            if (vertical == true)
            {
                printf("\n");
                printf("Birth date :\t\t");
            }

            printf("%d/", etudiant->date_of_birth->day);
            printf("%d/", etudiant->date_of_birth->month);
            printf("%d ", etudiant->date_of_birth->year);
        }

        if (etudiant->registration_date != null)
        {
            if (vertical == true)
            {
                printf("\n");
                printf("registration date :\t\t");
            }

            printf(" %d/", etudiant->registration_date->day);
            printf("%d/", etudiant->registration_date->month);
            printf("%d ", etudiant->registration_date->year);
        }
    }
    printf("\n");
}

void SearchForEtudiant(etd *etudiant)
{
    // TODO: implement this function
    printf("[SearchForEtudiant] is not implemnted \n");
    exit(EXIT_FAILURE);
}

void AdvanceSearchForEtudiant(etd *etudiant)
{
    // TODO: implement this function
    printf("[AdvanceSearchForEtudiant] is not implemnted \n");
    exit(EXIT_FAILURE);
}

int CountEtudiantsForSemester(sm *semestre)
{
    if (semestre->list_etudiant == null)
        return 0;

    int total = 0;
    etd *etudiant = semestre->list_etudiant;

    while (etudiant != null)
    {
        total++;
        etudiant = etudiant->next_etudiant;
    }
    // free(etudiant);
    return total;
}

int CountAllEtudiants(sm *list_of_semestres[numberOfSemesters])
{
    if (list_of_semestres == null)
        return 0;

    int total = 0;
    for (int i = 0; i < numberOfSemesters; i++)
    {
        total += CountEtudiantsForSemester(list_of_semestres[i]);
    }
    return total;
}

void showEtudiantForSemester(sm *semestre, bool decorate)
{
    if (semestre->list_etudiant == null)
        return;

    etd *etudiant = semestre->list_etudiant;

    if (decorate == true)
    {
        nicePrint(FgGreen, horizontal_line, FgReset, null, null);
        nicePrint(FgBlue, null, null, null, null);
    }

    if (semestre->level == Licence)
        printf("\t\t Semester S%d level Licence\n", semestre->number_of_semestre);
    else
        printf("\t\t Semester S%d level Master\n", semestre->number_of_semestre);

    if (decorate == true)
    {
        nicePrint(FgReset, " ", null, null, null);
        nicePrint(FgGreen, thickhorizontal_line, FgReset, null, null);

        printf("mtrcl\tfirstName\tsecondName\tmoyenne_generale \n");
        nicePrint(FgGreen, thickhorizontal_line, FgReset, null, null);
    }
    else
        printf("option\tmtrcl\tfirstName\tsecondName\tmoyenne_generale \n");

    int count = 1;
    while (etudiant != null)
    {
        if (decorate == false)
        {
            nicePrint(FgYellow, null, null, null, null);
            printf("%d \t", count);
            nicePrint(FgReset, null, null, null, null);

            count++;
        }

        displayEtudiantInfo(etudiant, false, false);
        etudiant = etudiant->next_etudiant;
    }

    if (decorate == true)
    {
        nicePrint(FgGreen, horizontal_line, FgReset, null, "\n\n");
    }
    // free(etudiant);
}

void ShowAllEtudiant(sm *list_of_semestres[numberOfSemesters])
{
    if (list_of_semestres == null)
        return;

    for (int i = 0; i < numberOfSemesters; i++)
    {
        showEtudiantForSemester(list_of_semestres[i], true);
    }
}

void calcMoyenForAllEtudiant(sm *list_of_semestres[numberOfSemesters])
{
    for (int i = 0; i < numberOfSemesters; i++)
    {
        calcMoyenForAllEtudiantOfSemester(list_of_semestres[i]);
    }
}

void calcMoyenForAllEtudiantOfSemester(sm *semester)
{
    if (semester->list_etudiant == null)
        return;

    etd *list_etudiant = semester->list_etudiant;

    while (list_etudiant != null)
    {
        calcMoyenForEtudiant(list_etudiant);
        list_etudiant = list_etudiant->next_etudiant;
    }
}

double calcMoyenForEtudiant(etd *etudiant)
{

    if (etudiant->list_modules_etudiant == null)
    {
        etudiant->moyenne_generale = numeric_null;
        return numeric_null;
    }

    modl *list_module = etudiant->list_modules_etudiant;

    int total_factors = 0;
    double total_score = 0;

    while (list_module != null)
    {
        total_factors += list_module->factor;

        double temp_moyn = calcModuleMoyen(list_module);

        if (temp_moyn == numeric_null)
        {
            etudiant->moyenne_generale = numeric_null;
            return numeric_null;
        }

        total_score += (temp_moyn * list_module->factor);

        list_module = list_module->next_module;
    }

    etudiant->moyenne_generale = (total_score / total_factors);
    return etudiant->moyenne_generale;
}

etd *getEtudiantByIndex(sm *semester, int index)
{
    if (semester->list_etudiant == null)
        return null;

    etd *temp_etudiant = semester->list_etudiant;
    int count = 1;

    while (temp_etudiant != null)
    {
        if (count == index)
            break;
        temp_etudiant = temp_etudiant->next_etudiant;
        count++;
    }
    return temp_etudiant;
}
// module funtions =========================================================

void createAndADDModuleTo(sm *semestre)
{
    modl *new_module = createModule(null, numeric_null, numeric_null);
    addModuletTo(new_module, semestre);
}

modl *createModule(char module_name[25], int factor, bool use_tp)
{
    modl *module = (modl *)malloc(sizeof(modl));
    if (module_name == null)
    {

        printf("insert module name : ");
        getchar();
        scanf("%[^\n]", module->module_name);
    }
    else
    {
        strcpy(module->module_name, module_name);
    }

    if (factor == numeric_null)
    {
        int option;
        while (true)
        {
            printf("\ninsert factor of module : ");
            scanf("%d", &option);
            if (option > 0)
            {
                module->factor = option;
                break;
            }
        }
    }
    else
    {
        module->factor = factor;
    }

    if (use_tp == true)
    {
        module->tp = numeric_null;
    }
    else if (use_tp == false)
    {
        module->tp = dont_use;
    }
    else
    {
        int option;
        while (true)
        {
            printf("\n\ndo you want to add tp to this module\n\n");
            nicePrint(FgYellow, "1", FgReset, "\t yes\n", null);
            nicePrint(FgYellow, "2", FgReset, "\t no\n", null);

            printf("\n\ninsert number : ");
            scanf("%d", &option);

            if (option == 1)
            {
                module->tp = numeric_null;
                break;
            }

            if (option == 2)
            {
                module->tp = dont_use;
                break;
            }
        }
    }

    module->td = numeric_null;
    module->examn = numeric_null;
    module->moyenne = numeric_null;

    module->next_module = null;

    return module;
}

void displayModuletInfo(modl *module, bool allInfo)

{
    if (allInfo == true)
    {
        printf("=======================\n");
        printf("module name : %s \n", module->module_name);
        if (module->tp == dont_use)
        {
            printf("module tp : not available \n");
        }
        else
        {
            if (module->tp != numeric_null)
                printf("module tp : %.2lf \n", module->tp);
            else
                printf("module tp : null \n");
        }

        if (module->td != numeric_null)
            printf("module td : %.2lf \n", module->td);
        else
            printf("module td : null \n");

        if (module->examn != numeric_null)
            printf("module examn : %.2lf \n", module->examn);
        else
            printf("module examn : null \n");

        if (module->moyenne != numeric_null)
            printf("module moyenne : %.2lf \n", module->moyenne);
        else
            printf("module moyenne : null \n");

        printf("=======================\n");
    }
    else
    {
        printf("%s\n", module->module_name);
    }
}

double calcModuleMoyen(modl *module)
{
    double temp_note;
    if (module->tp == dont_use)
    {
        if (module->td < 0 || module->examn < 0)
        {
            temp_note = numeric_null;
        }
        else
            temp_note = (module->td * 0.4) + (module->examn * 0.6);
    }
    else
    {
        if (module->td < 0 || module->tp < 0 || module->examn < 0)
        {
            temp_note = numeric_null;
        }
        else
        {
            temp_note = (((module->tp + module->td) / 2) * 0.4) + (module->examn * 0.6);
        }
    }

    module->moyenne = temp_note;
    return temp_note;
}

void addModuletTo(modl *module, sm *semestre)
{

    if (semestre->list_modules == null)
    {
        semestre->list_modules = module;
        addModuleToSemesterEtudiants(module, semestre->list_etudiant);

        return;
    }

    modl *temp_modl = semestre->list_modules;

    while (temp_modl->next_module != null)
    {
        temp_modl = temp_modl->next_module;
    }

    temp_modl->next_module = module;
    addModuleToSemesterEtudiants(module, semestre->list_etudiant);
}

void addModuleToSemesterEtudiants(modl *module, etd *etudiant_list)
{
    if (etudiant_list == null)
        return;

    etd *etudiant = etudiant_list;
    while (etudiant != null)
    {
        addModuleToEtudiant(module, etudiant);
        etudiant = etudiant->next_etudiant;
    }
}

void addModuleToEtudiant(modl *module, etd *etudiant)
{
    if (module == null)
    {
        printf("module is null \n");
        return;
    }

    if (etudiant == null)
    {
        printf("etudiant is null \n");
        return;
    }

    modl *copy_modl;

    if (module->tp == dont_use)
        copy_modl = createModule(module->module_name, module->factor, false);
    else
        copy_modl = createModule(module->module_name, module->factor, true);

    if (etudiant->list_modules_etudiant == null)
    {
        etudiant->list_modules_etudiant = copy_modl;
        return;
    }

    modl *list_module = etudiant->list_modules_etudiant;

    while (list_module->next_module != null)
    {
        list_module = list_module->next_module;
    }

    list_module->next_module = copy_modl;
}

void manualEditModule(modl *module, bool all_options)
{
    clear_screen();
    int option;

    if (all_options == true)
    {

        while (true)
        {
            printf("do you want to change module name? \n");
            nicePrint(FgYellow, "1 ", FgReset, "\t yes \n", null);
            nicePrint(FgYellow, "2 ", FgReset, "\t no \n", null);
            printf("\n insert number : ");
            scanf("%d", &option);

            if (option == 1)
            {
                printf("insert module name : ");
                getchar();
                scanf("%[^\n]", module->module_name);
                break;
            }
            else if (option == 2)
            {
                break;
            }
        }

        while (true)
        {
            printf("do you want to change Factor ? \n");
            nicePrint(FgYellow, "1 ", FgReset, "\t yes \n", null);
            nicePrint(FgYellow, "2 ", FgReset, "\t no \n", null);
            printf("\n insert number : ");
            scanf("%d", &option);

            if (option == 1)
            {
                insertNote(module, "insert Factor of module : ", 1);
                break;
            }
            else if (option == 2)
            {
                break;
            }
        }
    }

    if (module->tp != dont_use)
    {
        while (true)
        {
            printf("do you want to change TP? \n");
            nicePrint(FgYellow, "1 ", FgReset, "\t yes \n", null);
            nicePrint(FgYellow, "2 ", FgReset, "\t no \n", null);
            printf("\n insert number : ");
            scanf("%d", &option);

            if (option == 1)
            {
                insertNote(module, "insert TP note : ", 2);
                break;
            }
            else if (option == 2)
            {
                break;
            }
        }
    }

    while (true)
    {
        printf("do you want to change TD? \n");
        nicePrint(FgYellow, "1 ", FgReset, "\t yes \n", null);
        nicePrint(FgYellow, "2 ", FgReset, "\t no \n", null);
        printf("\n insert number : ");
        scanf("%d", &option);

        if (option == 1)
        {
            insertNote(module, "insert TD note : ", 3);
            break;
        }
        else if (option == 2)
        {
            break;
        }
    }

    while (true)
    {
        printf("do you want to change Examn? \n");
        nicePrint(FgYellow, "1 ", FgReset, "\t yes \n", null);
        nicePrint(FgYellow, "2 ", FgReset, "\t no \n", null);
        printf("\n insert number : ");
        scanf("%d", &option);

        if (option == 1)
        {
            insertNote(module, "insert Examn note : ", 4);
            break;
        }
        else if (option == 2)
        {
            break;
        }
    }
}

void editModule(modl *module, char module_name[25], int factor, double tp, double td, double examn, double moyenne)
{
    if (module_name != null)
    {
        strcpy(module->module_name, module_name);
    }

    if (factor > 0)
    {
        module->factor = factor;
    }

    if (tp == numeric_null)
        module->tp = numeric_null;
    else if (tp >= 0)
        module->tp = tp;

    if (td == numeric_null)
        module->td = numeric_null;
    else if (td >= 0)
        module->td = td;

    if (examn == numeric_null)
        module->examn = numeric_null;
    else if (examn >= 0)
        module->examn = examn;

    if (moyenne == numeric_null)
        module->moyenne = numeric_null;
    else if (moyenne >= 0)
        module->moyenne = moyenne;
}

void showEtudiantModules(etd *etudiant, bool allInfo)
{
    if (etudiant->list_modules_etudiant == null)
    {
        nicePrint(FgYellow, "there is no module found\n", FgReset, null, null);
        return;
    }

    modl *list_module = etudiant->list_modules_etudiant;

    int count = 1;
    while (list_module != null)
    {
        if (allInfo == true)
        {
            displayModuletInfo(list_module, true);
        }
        else
        {
            printf("%d ", count);
            displayModuletInfo(list_module, false);
        }
        count++;
        list_module = list_module->next_module;
    }
}

modl *getModuleByIndex(etd *etudiant, int index)
{
    if (etudiant->list_modules_etudiant == null)
        return null;

    modl *list_module = etudiant->list_modules_etudiant;

    int count = 1;
    while (list_module != null)
    {
        if (count == index)
        {
            break;
        }

        count++;
        list_module = list_module->next_module;
    }

    return list_module;
}

void restModule(modl *module)
{
    if (module->tp != dont_use)
    {
        module->tp = numeric_null;
    }

    module->td = numeric_null;
    module->examn = numeric_null;
    module->moyenne = numeric_null;
}

void showAllModuleForSemester(sm *semester)
{
    if (semester->list_modules == null)
    {
        printf("there is no moudels found in semester S%d\n\n", semester->number_of_semestre);
        return;
    }

    modl *module_list = semester->list_modules;

    nicePrint(FgGreen, horizontal_line, FgReset, null, null);
    nicePrint(FgCyan, "\t\t", null, null, null);
    printf("Semester S%d", semester->number_of_semestre);
    if (semester->level == Licence)
        printf(" Licence \n");
    else
        printf(" Master \n");

    nicePrint(FgGreen, thickhorizontal_line, FgReset, null, null);

    while (module_list != null)
    {
        displayModuletInfo(module_list, false);
        module_list = module_list->next_module;
    }

    nicePrint(FgGreen, horizontal_line, FgReset, null, null);
    printf("\n\n");
}
void showAllModule(sm *list_semester[numberOfSemesters])
{
    printf("All modules by semester\n");
    for (int i = 0; i < numberOfSemesters; i++)
    {
        showAllModuleForSemester(list_semester[i]);
    }
}

// Date function ==================================================================

date *createDate(int day, int month, int year)
{
    date *new_date = (date *)malloc(sizeof(date));
    int temp_day = day, temp_month = month, temp_year = year;

    while (true)
    {
        if (validateDay(temp_day) == true)
        {
            new_date->day = temp_day;
            break;
        }

        printf("insert day :");
        scanf("%d", &temp_day);
    }

    while (true)
    {
        if (validateMonth(temp_month) == true)
        {
            new_date->month = temp_month;
            break;
        }
        printf("insert month :");
        scanf("%d", &temp_month);
    }
    while (true)
    {
        if (validateYear(temp_year) == true)
        {
            new_date->year = temp_year;
            break;
        }
        printf("insert year :");
        scanf("%d", &temp_year);
    }

    return new_date;
}

bool validateDay(int day)
{
    if (day > 0 && day < 30)
        return true;
    return false;
}

bool validateMonth(int month)
{
    if (month > 0 && month < 13)
        return true;
    return false;
}

bool validateYear(int year)
{

    if (year > 1980 && year <= 2020)
        return true;
    return false;
}

date *getTodayDate()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    date *new_date = (date *)malloc(sizeof(date));
    new_date->day = tm.tm_mday;
    new_date->month = tm.tm_mon;
    new_date->year = tm.tm_year + 1900;

    return new_date;
}

void randomGenrateNotesForAllSemester(sm *list_of_semesters[numberOfSemesters])
{
    printf("Generate random number for all semesters \n");
    for (int i = 0; i < numberOfSemesters; i++)
    {
        randomGenrateNotesForSemester(list_of_semesters[i]);
    }
    printf("Done !\n");
}

void randomGenrateNotesForSemester(sm *semester)
{
    if (semester->list_etudiant == null)
        return;

    etd *list_etudiant = semester->list_etudiant;

    while (list_etudiant != null)
    {
        randomGenrateNotesForEtudiant(list_etudiant);
        list_etudiant = list_etudiant->next_etudiant;
    }
}

void randomGenrateNotesForEtudiant(etd *etudiant)
{
    if (etudiant->list_modules_etudiant == null)
        return;

    modl *list_module = etudiant->list_modules_etudiant;

    while (list_module != null)
    {
        if (list_module->tp != dont_use)
        {
            list_module->tp = getNumber(1, 10) + getNumber(0, 10);
        }

        list_module->td = getNumber(1, 10) + getNumber(0, 10);
        list_module->examn = getNumber(1, 10) + getNumber(0, 10);

        list_module = list_module->next_module;
    }
}

void showEtudiantsAdminsForAllSemesters(sm *list_semester[numberOfSemesters])
{
    printf("All Etudiants Admins \n\n");
    for (int i = 0; i < numberOfSemesters; i++)
    {
        showEtudiantsAdminsForSemester(list_semester[i]);
    }
}

void showEtudiantsAdminsForSemester(sm *semester)
{
    if (semester->list_etudiant == null)
        return;

    etd *list_etudiant = semester->list_etudiant;

    nicePrint(FgYellow, horizontal_line, FgReset, null, null);
    printf("\t\tSemester S%d \n", semester->number_of_semestre);
    nicePrint(FgYellow, thickhorizontal_line, FgReset, null, null);

    while (list_etudiant != null)
    {
        if (list_etudiant->moyenne_generale == numeric_null)
        {
            calcMoyenForEtudiant(list_etudiant);
        }

        if (isEtudiantAdmin(list_etudiant) == true)
        {
            printf("\t%s\t%s : %.2lf \n", list_etudiant->first_name, list_etudiant->second_name, list_etudiant->moyenne_generale);
        }

        list_etudiant = list_etudiant->next_etudiant;
    }
    nicePrint(FgYellow, horizontal_line, FgReset, "\n\n\n", null);
}

bool isEtudiantAdmin(etd *etudiant)
{
    if (etudiant == null)
        return false;

    if (etudiant->moyenne_generale == numeric_null)
        return false;

    if (etudiant->moyenne_generale > 10)
        return true;

    return false;
}

void showStatisticsForAllSomester(sm *list_semester[numberOfSemesters], int type)
{
    int *admins = (int *)malloc(sizeof(int));
    int *ajournes = (int *)malloc(sizeof(int));
    int *notCalc = (int *)malloc(sizeof(int));

    *admins = 0;
    *ajournes = 0;
    *notCalc = 0;

    countEtudiantStateByAllSomester(list_semester, admins, ajournes, notCalc);

    int total = *admins + *ajournes + *notCalc;

    if (total == 0)
    {
        printf("nothing to show \n\n");
        return;
    }

    double admins_percentage = (double)(*admins * 100) / total;
    double ajournes_percentage = (double)(*ajournes * 100) / total;
    double notCalc_percentage = (double)(*notCalc * 100) / total;

    if (type == 1 || type == 0)
    {
        printf("\nadmins %d \n", *admins);
        nicePrint("Etudiants that are Admins : ", FgGreen, null, null, null);
        printf("%.2lf %% \n", admins_percentage);
        printPercentage((int)admins_percentage, true);
        nicePrint(FgReset, null, null, null, null);
    }

    if (type == 2 || type == 0)
    {
        printf("\nAjournes %d \n", *ajournes);
        nicePrint("Etudiants that are Ajournes : ", FgRed, null, null, null);
        printf("%.2lf %%\n", ajournes_percentage);
        printPercentage((int)ajournes_percentage, true);
        nicePrint(FgReset, null, null, null, null);
    }

    if (type == 3 || type == 0)
    {
        printf("\nnot calculated %d \n", *notCalc);
        nicePrint("Etudiants that are not calculated yet : ", FgYellow, null, null, null);
        printf("%.2lf %%\n", notCalc_percentage);
        printPercentage((int)notCalc_percentage, true);
        nicePrint(FgReset, null, null, null, null);
    }

    if (type == 0)
    {

        printf("\nAll percentage for All Semesters \n");

        printf("|");

        nicePrint(FgGreen, null, null, null, null);
        printPercentage((int)admins_percentage, false);

        nicePrint(FgRed, null, null, null, null);
        printPercentage((int)ajournes_percentage, false);

        nicePrint(FgYellow, null, null, null, null);
        printPercentage((int)notCalc_percentage, false);

        nicePrint(FgReset, null, null, null, null);
        printf("|\n\n");
    }

    free(admins);
    free(ajournes);
    free(notCalc);
}

void showStatisticsForSomester(sm *semester)
{
    int *admins = (int *)malloc(sizeof(int));
    int *ajournes = (int *)malloc(sizeof(int));
    int *notCalc = (int *)malloc(sizeof(int));

    *admins = 0;
    *ajournes = 0;
    *notCalc = 0;

    countEtudiantStateBySomester(semester, admins, ajournes, notCalc);

    int total = *admins + *ajournes + *notCalc;

    if (total == 0)
        return;

    nicePrint(FgGreen, horizontal_line, FgReset, null, null);
    nicePrint(FgCyan, null, null, null, null);
    printf("total number of Etudiant by Semester S%d \n", semester->number_of_semestre);
    nicePrint(FgGreen, horizontal_line, FgReset, null, null);
    printf("Show Statistics \n");

    double admins_percentage = (*admins * 100) / total;
    double ajournes_percentage = (*ajournes * 100) / total;
    double notCalc_percentage = (*notCalc * 100) / total;

    nicePrint("Etudiants that are Admins : ", FgGreen, null, null, null);
    printf("%.2lf %%\n", admins_percentage);
    printPercentage((int)admins_percentage, true);
    nicePrint(FgReset, null, null, null, null);

    nicePrint("Etudiants that are Ajournes : ", FgRed, null, null, null);
    printf("%.2lf %%\n", ajournes_percentage);
    printPercentage((int)ajournes_percentage, true);
    nicePrint(FgReset, null, null, null, null);

    nicePrint("Etudiants that are not calculated yet : ", FgYellow, null, null, null);
    printf("%.2lf %%\n", notCalc_percentage);
    printPercentage((int)notCalc_percentage, true);
    nicePrint(FgReset, null, null, null, null);

    printf("\nAll percentage for Semester S%d \n", semester->number_of_semestre);

    printf("|");

    nicePrint(FgGreen, null, null, null, null);
    printPercentage((int)admins_percentage, false);

    nicePrint(FgRed, null, null, null, null);
    printPercentage((int)ajournes_percentage, false);

    nicePrint(FgYellow, null, null, null, null);
    printPercentage((int)notCalc_percentage, false);

    nicePrint(FgReset, null, null, null, null);
    printf("|\n\n");

    free(admins);
    free(ajournes);
    free(notCalc);
    printf("\n\n\n\n\n");
}

void printPercentage(int number, bool addBars)
{
    if (addBars == true)
        printf("|");
    for (int i = 0; i < number; i++)
    {
        printf("=");
    }
    if (addBars == true)
        printf("|\n");
}

void countEtudiantStateByAllSomester(sm *list_semester[numberOfSemesters], int *admins, int *ajournes, int *notCalc)
{
    for (size_t i = 0; i < numberOfSemesters; i++)
    {
        countEtudiantStateBySomester(list_semester[i], admins, ajournes, notCalc);
    }
}

void countEtudiantStateBySomester(sm *semester, int *admins, int *ajournes, int *notCalc)
{
    if (semester->list_etudiant == null)
        return;

    etd *list_etudiant = semester->list_etudiant;

    while (list_etudiant != null)
    {
        countEtudiantByState(list_etudiant, admins, ajournes, notCalc);

        list_etudiant = list_etudiant->next_etudiant;
    }
}

void countEtudiantByState(etd *etudiant, int *admins, int *ajournes, int *notCalc)
{
    if (etudiant == null)
        return;

    calcMoyenForEtudiant(etudiant);

    if (etudiant->moyenne_generale == numeric_null)
    {
        if (notCalc != null)
            *notCalc = *notCalc + 1;
    }
    else if (etudiant->moyenne_generale >= 10)
    {
        if (admins != null)
            *admins = *admins + 1;
    }
    else if (etudiant->moyenne_generale < 10 && etudiant->moyenne_generale >= 0)
    {
        if (ajournes != null)
            *ajournes = *ajournes + 1;
    }
    else
    {
        if (notCalc != null)
            *notCalc = *notCalc + 1;
    }
}

// Init Function =====================================================================

void init()
{
    struct Semestre *list_semestre[10];

    for (int i = 0; i < numberOfSemesters; i++)
    {
        enum Level lvl;
        if (i + 1 <= 6)
            lvl = Licence;
        else
            lvl = Master;

        list_semestre[i] = createSemestre(lvl, i + 1);
    }

    int option = 0;
    while (true)
    {
        clear_screen();
        printf("do you want to preload data \n");
        nicePrint(FgYellow, "1 ", FgReset, "yes\n", null);
        nicePrint(FgYellow, "2 ", FgReset, "no\n", null);
        scanf("%d", &option);

        if (option == 1)
        {
            break;
        }
        else if (option == 2)
        {
            return dashboard(list_semestre);
        }
    }

    char *fNames[] = {
        "Loofy", "Kersti", "Florno", "Latos",
        "Terry", "Joann", "Kary", "Aide", "Maggie", "Christ",
        "Sandy", "Tesha", "Laver", "Nancie", "Hailey", "Aiko",
        "Florae", "Belva", "Joy", "Shenna", "Vella", "Nelda",
        "Shyla", "Merlin", "Brinda", "Denna", "Desir", "Elean",
        "Makeda", "Robbyn", "Harry", "Maria", "Marisha", "Dacia",
        "Cyndi", "Cletus", "Katharyn", "Kasey", "Efrain", "Palma",
        "Evette", "Jenee", "Vikki", "Clifford", "Serita", "Leann",
        "Tom", "Claudine", "Meda", "Angela", "Dean", "Fredia", "Renata",
        "Milo", "Briana", "Normand", "Trinh", "Elsie", "Raven", "Carmina",
        "Naruto", "Celsa", "Toney", "Terrie", "Blaine", "Stephnie", "Michale",
        "Vincenzo", "Dewey", "Candance", "Chandra", "June", "Tracey",
        "Apolonia", "Qiana", "Walter", "Season", "Brunilda", "Irena",
        "Melani", "Deeanna", "Angelique", "Han", "Buster", "Salvador",
        "Mathew", "Mike", "Norris", "Venita", "Rubye", "Dannette",
        "Cristen", "Maegan", "Stasia", "Luba", "Melonie", "Matilde",
        "Christin", "Keturah", "Lakendra"};

    char *sNames[] = {
        "Mehrng", "Replle", "Leff", "Picks", "Simek", "Carlo",
        "Helman", "Catan", "Saman", "Ingeni", "Ohlsen",
        "Mynat", "Hufman", "Ringo", "Paman", "Appel",
        "Howin", "Gracie", "Graeda", "Dawes",
        "Hyden", "Maill", "Smith", "Dinle",
        "Easter", "Igo", "Stinnett", "Hasell",
        "Narron", "Coco", "Cotner", "Biinger",
        "Lease", "Widmer", "Wolk", "Orvis", "Hoisington",
        "Gil", "Grafton", "Low", "Fyfe", "Cranor", "Marcinko",
        "Mersch", "Gokey", "Shuey", "Kall", "Custard", "Ewin",
        "Viverette", "Redwine", "Schapiro", "Lotz", "Leonhardt",
        "Bufkin", "Hick", "Broach", "Amoroso", "Culbreath", "Dunford",
        "Granada", "Showman", "Vore", "Phan", "Hurlbut", "Collington",
        "Borgmeyer", "Petri", "Rodd", "Culligan", "Chute", "Crawley",
        "Ekberg", "Galdamez", "Lawhon", "Clow", "Atchinson", "Rahaim",
        "Adolphsen", "Rager", "Carbonneau", "Doran", "Hanscom", "Anello",
        "Villafane", "Sterrett", "Vanderslice", "Scalzo", "Flood", "Ahearn",
        "Crete", "Denker", "Lamoureux", "Jeong", "Maeda", "Pinon", "Dederick",
        "Neilsen", "Scala", "Strawder"};

    char *modules_name[] = {
        "Math", "Algo", "structural machine", "Analyse",
        "Algabre", "Physique", "Python", "POO"};

    bool add_tp[] = {false, true, false, false, false, false, true, true};
    int factors_modules[] = {3, 4, 4, 4, 3, 2, 2, 2};

    int random_number;
    int random_day;
    date *new_date = (date *)malloc(sizeof(date));

    new_date->day = 1;
    new_date->month = 1;
    new_date->year = 1995;

    clear_screen();

    printf("Generate etudiant \n");
    for (int i = 0; i < numberOfSemesters; i = i + 2)
    {
        for (int j = 0; j < 25; j++)
        {
            random_number = j;
            etd *new_etudiant = createEtudiant(fNames[random_number], sNames[random_number], new_date);
            addEtudiantTo(new_etudiant, list_semestre[i]);
            new_etudiant = createEtudiant(fNames[random_number], sNames[random_number], new_date);
            int index = i + 1;
            addEtudiantTo(new_etudiant, list_semestre[index]);
        }
    }
    printf("Done !\n");

    modl *new_module;

    printf("Generate Modules for semesters \n");
    for (int i = 0; i < numberOfSemesters; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            new_module = createModule(modules_name[j], factors_modules[j], add_tp[j]);
            addModuletTo(new_module, list_semestre[i]);
        }
    }
    printf("Done !\n");

    printf("Generate random Notes for all semesters \n");
    for (int i = 0; i < numberOfSemesters; i++)
    {
        randomGenrateNotesForSemester(list_semestre[i]);
    }
    printf("Done !\n");

    nicePrint(FgYellow, "Press enter to continue \n", FgReset, null, null);
    getchar();
    getchar();

    dashboard(list_semestre);
}
