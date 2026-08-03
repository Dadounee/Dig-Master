/*

    the goal is to make a universal button creator + handler

typedef void    clickAction(void *);
typedef void    displayFunction(void *, float);

typedef enum    e_btnState {
    DISABLED,
    DEACTIVATED,
    ACTIVE
} btnState;

typedef struct s_button_data {
    int             id;
    btnState        state;

    Color           hoverTint;
    Rectangle       collRect;
    clickAction     *action;
    displayFunction *ui;
} button;

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
        Buttons->max = 0;
        Buttons->count = 0;
        Buttons->existing_count = 0;
        Buttons->btnsPtr = NULL;
    }

    return (Buttons);
}

/*

    create a "global" button var keeping track off all buttons

*/
int    addButton(button *new)
{
    gButtonData *buttons = getButtons();

    if (!buttons->count)
    {
        buttons->max++;
        buttons->btnsPtr = malloc(buttons->max * sizeof(button *));
        buttons->btnsPtr[buttons->count++] = new;
    }
    else if (buttons->count == buttons->max)
    {
        buttons->max *= 2;
        buttons->btnsPtr = realloc(buttons->btnsPtr, buttons->max * sizeof(button *));
        buttons->btnsPtr[buttons->count++] = new;
    }
    else
        buttons->btnsPtr[buttons->count++] = new;
    buttons->existing_count++;
    return (buttons->count - 1);
}

/*

    Will create a button using 2 handlers, a collide rect and a color and add it to the buttons list

    notes:
        no collide rect results in a init abort (NULL returned)
        no clickHandler will result in a warning (and a useless button)
        no displayHandler will result on a black rectangle for ui with tint and a warning
        BLACK is normal hover

*/
button  *createButton(clickAction *clickHandler, displayFunction *displayHandler, Rectangle collideRect,
                    void *clickDependency, void *uiDependency1, void *uiDependency2)
{
    if (collideRect.height == 0 || collideRect.width == 0)
    {
        printf("\tBUTTON: aborting due to empty collideRect provided\n");
        return (NULL);
    }
    if (!clickHandler) { printf("\tBUTTON: WARNING: no click handler provided\n"); }
    if (!displayHandler) { printf("\tBUTTON: WARNING: no display handler provided\n"); }

    button  *new = malloc(sizeof(button));

    new->action = clickHandler;
    new->ui = displayHandler;
    new->collRect = collideRect;

    new->uiDependency1 = uiDependency1;
    new->uiDependency2 = uiDependency2;
    new->clickDependency = clickDependency;

    new->id = addButton(new);

    return (new);
}

/*

    free the button

*/
void    removeButton(int id)
{
    gButtonData  *Buttons = getButtons();

    if (id > Buttons->count) { return ; }
    if (Buttons->btnsPtr[id])
    {
        free(Buttons->btnsPtr[id]);
        Buttons->btnsPtr[id] = NULL;
        Buttons->existing_count--;
    }
    
    // this section is here to see if we can optimise space taken
    int i = 0;

    while(i < 31)
    {
        if ((1 << i) == Buttons->existing_count)
        {
            int     newCount = 0;
            button  **newBtnsPtr = malloc(sizeof(Buttons->existing_count * sizeof(button *)));

            for (i = 0; i < Buttons->count; i++)
            {
                if (Buttons->btnsPtr[i])
                {
                    newBtnsPtr[newCount++] = Buttons->btnsPtr[i];
                    if (newCount == Buttons->existing_count)
                        break;
                }
                i++;
            }
            free(Buttons->btnsPtr);
            Buttons->btnsPtr = newBtnsPtr;
            Buttons->max = Buttons->existing_count;
            return ;
        }
        i++;
    }
}
void    refreshButton(int id, Vector2 cursorPos)
{
    gButtonData  *Buttons = getButtons();

    if (Buttons->btnsPtr[id] && Buttons->btnsPtr[id]->state != DISABLED)
    {
        if (Buttons->btnsPtr[id]->isHoverable && cursorPos.x > Buttons->btnsPtr[id]->collRect.x &&
            cursorPos.x < Buttons->btnsPtr[id]->collRect.x + Buttons->btnsPtr[id]->collRect.width &&
            cursorPos.y > Buttons->btnsPtr[id]->collRect.y &&
            cursorPos.y < Buttons->btnsPtr[id]->collRect.y + Buttons->btnsPtr[id]->collRect.height)
        {
            Buttons->btnsPtr[id]->ui(Buttons->btnsPtr[id]->uiDependency1, Buttons->btnsPtr[id]->uiDependency2, true);
        }
        Buttons->btnsPtr[id]->ui(Buttons->btnsPtr[id]->uiDependency1, Buttons->btnsPtr[id]->uiDependency2, false);
    }
}

/*

    check if click is on an active button then exec button's job

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

    refresh the active buttons display

*/
void    displayButtons(Vector2 cursorPos)
{
    gButtonData  *Buttons = getButtons();

    for (int i = 0; i < Buttons->count; i++)
    {
        if (Buttons->btnsPtr[i] && Buttons->btnsPtr[i]->state != DISABLED)
        {
            if (Buttons->btnsPtr[i]->isHoverable && cursorPos.x > Buttons->btnsPtr[i]->collRect.x &&
                cursorPos.x < Buttons->btnsPtr[i]->collRect.x + Buttons->btnsPtr[i]->collRect.width &&
                cursorPos.y > Buttons->btnsPtr[i]->collRect.y &&
                cursorPos.y < Buttons->btnsPtr[i]->collRect.y + Buttons->btnsPtr[i]->collRect.height)
            {
                Buttons->btnsPtr[i]->ui(Buttons->btnsPtr[i]->uiDependency1, Buttons->btnsPtr[i]->uiDependency2, true);
            }
            Buttons->btnsPtr[i]->ui(Buttons->btnsPtr[i]->uiDependency1, Buttons->btnsPtr[i]->uiDependency2, false);
        }
    }
}

/*

    free all buttons + button buffer

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
