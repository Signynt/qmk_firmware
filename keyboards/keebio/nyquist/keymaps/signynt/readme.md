# Signynt Nyquist Rev. 3

Port of [the personal Cygnus keymap](https://github.com/Signynt/zmk-config/blob/master/config/cygnus.keymap).

Uses `LAYOUT_ortho_4x12`. The five Cygnus columns sit nearest the center on each half. The outermost column is disabled on all seven non-gaming layers. The six Cygnus thumb keys occupy the three innermost bottom-row keys on each half; the remaining bottom-row positions are disabled outside gaming.

Base thumbs, from left to right:

| Left outer thumb | Left middle thumb | Left inner thumb | Right inner thumb | Right middle thumb | Right outer thumb |
| --- | --- | --- | --- | --- | --- |
| Escape / MEDR | Space / NAVR | Tab / MOUS | Enter / NSSL | Backspace / NSL | Disabled |

Tap for the key, hold for the layer. Hold Enter, then the left outer thumb for FUNL. Edge mod-taps use the source's left-side Alt, Shift, and Ctrl modifiers, a 160 ms tapping term, and balanced hold behavior. Layer-taps use 200 ms and hold on another key press. Shifted-symbol mod-taps emit the complete shifted symbol on tap.

## Gaming

Hold the Space/NAVR thumb and tap the Escape/MEDR thumb to toggle GAME. Hold the left innermost gaming thumb for SECGAME, then tap the top-left key to exit gaming.

GAME expands to six columns on each half:

```text
Esc   Q     W     E     R     T       Y     U     I     O     P     Bksp
Shift A     S     D     F     G       H     J     K     L     '     Enter
Ctrl  Z     X     C     V     B       N     M     ,     .     /     Shift
Alt   GUI   ---   Tab   Space SECGAME Enter Bksp  Del   ---   ---   Ctrl
```

SECGAME retains the source's left number pad, right F keys, volume controls, and right Alt thumb. T/G/B remain available in the new inner left column, with R/F/V beside them. Gaming uses plain keys without mod-taps.

## Platform adaptations

Bluetooth selection/clearing bindings on MEDR are disabled because the Nyquist is wired. All other source layers, transparent bindings, Yabai shortcuts, media controls, Caps Word, mouse controls, and the screenshot tap dance are retained. Mouse movement uses approximately 1200 units/second before host pointer scaling. Screenshot: one tap sends GUI+Shift+S; two taps send Ctrl+Shift+4. Host keyboard layout and shortcut configuration must match the Cygnus setup.

## Build and flash

```sh
qmk compile -kb keebio/nyquist/rev3 -km signynt
qmk flash -kb keebio/nyquist/rev3 -km signynt
```
