#include <stdio.h>
#include "todo.h"

int main()
{
    Pesanan p1, p2;
    List todo;
    List inprogress;
    CreateTodoList(&todo);
    CreateTodoList(&inprogress);
    CreatePesanan(5, 'A', 'B', 'N', -1, &p1);
    CreatePesanan(1, 'B', 'C', 'H', -1, &p2);

    insertFirst(&todo, p1);
    insertFirst(&inprogress, p2);

    displayTodo(todo);
    displayInProgress(inprogress);

    deleteFirst(&todo);
    deleteFirst(&inprogress);

    displayTodo(todo);
    displayInProgress(inprogress);
    return 0;
}