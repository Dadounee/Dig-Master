#ifndef BUTTONDATA_H
# define BUTTONDATA_H

# include "raylib.h"

typedef void    clickAction(void *);
typedef void    displayFunction(void *, float);

typedef struct s_button_data {
    int             id;

    Color           hoverTint;
    Rectangle       butnRect;
    clickAction     *action;
    displayFunction *ui;
} button;

#endif