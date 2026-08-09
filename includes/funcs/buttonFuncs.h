#ifndef BUTTONFUNCS_H
# define BUTTONFUNCS_H

# include "buttonData.h"
    
    int     addButton(Button *new);

    void    clearButtons(void);
    void    removeButton(int id);
    void    removeButtonNamed(char *name);
    void    executeClicks(Vector2 clickPos);
    void    displayButtons(Vector2 cursorPos);
    void    refreshButton(int id, Vector2 cursorPos);
    void    refreshButtonName(char *name, Vector2 cursorPos);
    void    changeButtonState(int id, btnState state);
    void    changeButtonStateName(char *name, btnState state);

    int     createButton(char *name, clickAction *clickHandler, displayFunction *displayHandler, Rectangle collideRect,
        void *clickDependency, void *uiDependency1, void *uiDependency2, bool isHoverable);





    // button creation related functions here
    void    invButtonClick(void *infos);
    void    invButtonDisplay(void *infos, void *infos2, bool isHovered);
    void    returnBtnClick(void *infos);
    void    returnBtnDisplay(void *infos, void *infos2, bool isHovered);
    void    sellButtonClick(void *infos);
    void    sellButtonDisplay(void *infos, void *infos2, bool isHovered);

#endif