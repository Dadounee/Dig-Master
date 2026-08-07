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
        char            *name;
        btnState        state;

        int             isHoverable;
        Rectangle       collRect;
        clickAction     *action;
        displayFunction *ui;

        void            *clickDependency;
        void            *uiDependency1;
        void            *uiDependency2;
    } Button;

    typedef struct s_gButtonData
    {
        int     id;
        int     max;
        int     count;
        int     existing_count;

        Button  **btnsPtr;

    } gButtonData;

#endif