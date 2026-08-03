#ifndef BUTTONFUNCS_H
# define BUTTONFUNCS_H

# include "buttonData.h"
    
int     addButton(Button *new);

void    clearButtons(void);
void    removeButton(int id);
void    executeClicks(Vector2 clickPos);
void    displayButtons(Vector2 cursorPos);
void    refreshButton(int id, Vector2 cursorPos);
void    changeButtonState(int id, btnState state);

int     createButton(clickAction *clickHandler, displayFunction *displayHandler, Rectangle collideRect,
    void *clickDependency, void *uiDependency1, void *uiDependency2, int isHoverable);

#endif