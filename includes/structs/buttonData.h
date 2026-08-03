#ifndef BUTTONDATA_H
# define BUTTONDATA_H

# include "raylib.h"

    typedef void    clickAction(void *infos);
    typedef void    displayFunction(void *infos, void *infos2, bool isHovered);

    typedef enum    e_btnState {
        DISABLED,
        DEACTIVATED,
        ACTIVE
    } btnState;

    typedef struct s_button_data {
        int             id;
        btnState        state;

        int             isHoverable;
        Rectangle       collRect;
        clickAction     *action;
        displayFunction *ui;

        void            *clickDependency;
        void            *uiDependency1;
        void            *uiDependency2;
    } button;

    typedef struct s_gButtonData
    {
        int     max;
        int     count;
        int     existing_count;

        button  **btnsPtr;

    } gButtonData;
    
# define BUTTON_ACTIVATE(btn)   ((btn)->state = ACTIVE)
# define BUTTON_DISABLE(btn)    ((btn)->state = DISABLED)
# define BUTTON_DEACTIVATE(btn) ((btn)->state = DEACTIVATED)

#endif