/*

    the goal is to make a universal Button creator + handler

typedef void    clickAction(void *);
typedef void    displayFunction(void *, float);

typedef enum    e_btnState {
    DISABLED,
    DEACTIVATED,
    ACTIVE
} btnState;

typedef struct s_Button_data {
    int             id;
    btnState        state;

    Color           hoverTint;
    Rectangle       collRect;
    clickAction     *action;
    displayFunction *ui;
} Button;

*/
#include "buttonData.h"
#include <stdlib.h>
#include <stdio.h>

gButtonData    *getButtons(void)
{
    static gButtonData  *Buttons = {0};

    if (!Buttons)
    {
        Buttons = malloc(sizeof(gButtonData));
        Buttons->id = 0;
        Buttons->max = 0;
        Buttons->count = 0;
        Buttons->existing_count = 0;
        Buttons->btnsPtr = NULL;
    }

    return (Buttons);
}

/*

    create a "global" Button var keeping track off all Buttons

*/
int    addButton(Button *new)
{
    gButtonData *Buttons = getButtons();

    if (!Buttons->count)
    {
        Buttons->max++;
        Buttons->btnsPtr = malloc(Buttons->max * sizeof(Button *));
        Buttons->btnsPtr[Buttons->count++] = new;
    }
    else if (Buttons->count == Buttons->max)
    {
        Buttons->max *= 2;
        Buttons->btnsPtr = realloc(Buttons->btnsPtr, Buttons->max * sizeof(Button *));
        Buttons->btnsPtr[Buttons->count++] = new;
    }
    else
        Buttons->btnsPtr[Buttons->count++] = new;
    Buttons->id++;
    Buttons->existing_count++;
    return (Buttons->id - 1);
}

/*

    Will create a Button using 2 handlers, a collide rect and a color and add it to the Buttons list

    notes:
        no collide rect results in a init abort (NULL returned)
        no clickHandler will result in a warning (and a useless Button)
        no displayHandler will result on a black rectangle for ui with tint and a warning
        BLACK is normal hover

    returns id if you want to update or remove button by hand

*/
int  createButton(clickAction *clickHandler, displayFunction *displayHandler, Rectangle collideRect,
                    void *clickDependency, void *uiDependency1, void *uiDependency2, int isHoverable)
{
    if (collideRect.height == 0 || collideRect.width == 0 || !clickHandler)
    {
        printf("\tBUTTON: aborting due to empty collideRect or no click handler provided\n");
        return (-1);
    }
    if (!displayHandler) { printf("\tBUTTON: WARNING: no display handler provided\n"); }

    Button  *new = malloc(sizeof(Button));

    new->action = clickHandler;
    new->ui = displayHandler;
    new->collRect = collideRect;

    new->uiDependency1 = uiDependency1;
    new->uiDependency2 = uiDependency2;
    new->clickDependency = clickDependency;

    new->id = addButton(new);
    new->state = ACTIVE;
    new->isHoverable = isHoverable;

    return (new->id);
}

/*

    free the Button

*/
void    removeButton(int id)
{
    gButtonData  *Buttons = getButtons();

    if (id > Buttons->count) { return ; }
    for (int i = 0; i < Buttons->count; i++)
    {
        if (Buttons->btnsPtr[i] && Buttons->btnsPtr[i]->id == id)
        {
            free(Buttons->btnsPtr[i]);
            Buttons->btnsPtr[i] = NULL;
            Buttons->existing_count--;
        }
    }
    
    // this section is here to see if we can optimise space taken
    int i = 0;

    while(i < 31)
    {
        if ((1 << i) == Buttons->existing_count)
        {
            int     newCount = 0;
            Button  **newBtnsPtr = malloc(Buttons->existing_count * sizeof(Button *));

            for (i = 0; i < Buttons->count; i++)
            {
                if (Buttons->btnsPtr[i])
                {
                    newBtnsPtr[newCount] = Buttons->btnsPtr[i];
                    newCount++;
                    if (newCount == Buttons->existing_count)
                        break;
                }
            }
            free(Buttons->btnsPtr);
            Buttons->btnsPtr = newBtnsPtr;
            Buttons->max = Buttons->existing_count;
            Buttons->count = Buttons->existing_count;
            break ;
        }
        i++;
    }
}
void    refreshButton(int id, Vector2 cursorPos)
{
    gButtonData  *Buttons = getButtons();

    for (int i = 0;i < Buttons->count; i++)
    {
        if (Buttons->btnsPtr[i] && Buttons->btnsPtr[i]->id != id)
            continue ;
        if (Buttons->btnsPtr[i] && Buttons->btnsPtr[i]->state != DISABLED)
        {

            if (Buttons->btnsPtr[i]->isHoverable && cursorPos.x > Buttons->btnsPtr[i]->collRect.x &&
            cursorPos.x < Buttons->btnsPtr[i]->collRect.x + Buttons->btnsPtr[i]->collRect.width &&
            cursorPos.y > Buttons->btnsPtr[i]->collRect.y &&
            cursorPos.y < Buttons->btnsPtr[i]->collRect.y + Buttons->btnsPtr[i]->collRect.height)
            {
                Buttons->btnsPtr[i]->ui(Buttons->btnsPtr[i]->uiDependency1, Buttons->btnsPtr[i]->uiDependency2, true);
                break;
            }
            Buttons->btnsPtr[i]->ui(Buttons->btnsPtr[i]->uiDependency1, Buttons->btnsPtr[i]->uiDependency2, false);
            break;
        }
    }
}
    
    /*

    check if click is on an active Button then exec Button's job

*/
void    executeClicks(Vector2 clickPos)
{
    gButtonData  *Buttons = getButtons();

    for (int i = 0; i < Buttons->count; i++)
    {
        if (Buttons->btnsPtr[i] && Buttons->btnsPtr[i]->state == ACTIVE)
        {
            if (clickPos.x > Buttons->btnsPtr[i]->collRect.x &&
                clickPos.x < Buttons->btnsPtr[i]->collRect.x + Buttons->btnsPtr[i]->collRect.width &&
                clickPos.y > Buttons->btnsPtr[i]->collRect.y &&
                clickPos.y < Buttons->btnsPtr[i]->collRect.y + Buttons->btnsPtr[i]->collRect.height)
            {
                Buttons->btnsPtr[i]->action(Buttons->btnsPtr[i]->clickDependency);
            }
        }
    }
}

/*

    refresh the active Buttons display

*/
void    displayButtons(Vector2 cursorPos)
{
    gButtonData  *Buttons = getButtons();

    for (int i = 0; i < Buttons->count; i++)
    {
        if (Buttons->btnsPtr[i] && Buttons->btnsPtr[i]->state != DISABLED)
        {
            if (!Buttons->btnsPtr[i]->ui)
            {
                DrawRectangleRec(Buttons->btnsPtr[i]->collRect, LIGHTGRAY);
                continue ;
            }
            if (Buttons->btnsPtr[i]->isHoverable && Buttons->btnsPtr[i]->state == ACTIVE &&
                cursorPos.x > Buttons->btnsPtr[i]->collRect.x &&
                cursorPos.x < Buttons->btnsPtr[i]->collRect.x + Buttons->btnsPtr[i]->collRect.width &&
                cursorPos.y > Buttons->btnsPtr[i]->collRect.y &&
                cursorPos.y < Buttons->btnsPtr[i]->collRect.y + Buttons->btnsPtr[i]->collRect.height)
            {
                Buttons->btnsPtr[i]->ui(Buttons->btnsPtr[i]->uiDependency1, Buttons->btnsPtr[i]->uiDependency2, true);
                continue ;
            }
            Buttons->btnsPtr[i]->ui(Buttons->btnsPtr[i]->uiDependency1, Buttons->btnsPtr[i]->uiDependency2, false);
        }
    }
}

/*

    free all Buttons + Button buffer

*/
void    clearButtons(void)
{
    gButtonData  *Buttons = getButtons();

    for (int i = 0 ; i < Buttons->count ; i++)
    {
        if (Buttons->btnsPtr[i])
        {
            free(Buttons->btnsPtr[i]);
            Buttons->btnsPtr[i] = NULL;
        }
    }
    if (Buttons->btnsPtr)
        free(Buttons->btnsPtr);
    free(Buttons);
}

void changeButtonState(int id, btnState state)
{
    gButtonData  *Buttons = getButtons();

    if (id >= 0 && id < Buttons->id)
    {
        for (int i = 0;i < Buttons->count;i++)
        {
            if (Buttons->btnsPtr[i] && Buttons->btnsPtr[i]->id == id)
            {
                Buttons->btnsPtr[id]->state = state;
                break;
            }
        }
    }
}
