#ifndef TLINSUIUTILS_H
#define TLINSUIUTILS_H

#define tlinsWSetWidget(w, wl, destw) \
    {                                 \
        QSize s;                      \
        s = (w).size();               \
        (destw)->resize(s);           \
        (wl).addWidget(&(w));         \
        (destw)->setLayout(&(wl));    \
    }

#define tlinsWUpdateWidget(w, wl, destw)      \
    {                                         \
        QSize s;                              \
        s = (w).size();                       \
        if ((wl).widget() != NULL) {          \
            (wl).removeWidget((wl).widget()); \
        }                                     \
        (wl).addWidget(&(w));                 \
        (destw)->resize(s);                   \
    }

#endif // TLINSUIUTILS_H
