#include <stdio.h>
#include <CoreGraphics/CoreGraphics.h>

#define DSPL_MAX_DISPLAYS 32

int main(int argc, char **argv)
{
    CGDirectDisplayID dspls[DSPL_MAX_DISPLAYS];
    UInt32 count = 0;
    CGError err = CGGetActiveDisplayList(DSPL_MAX_DISPLAYS, dspls, &count);
    if (err != kCGErrorSuccess) {
        printf("CGGetActiveDisplayList error\n");
        return -1;
    }

    for (int i = 0; i < count; i++) {
        CGDirectDisplayID dspl = dspls[i];
        CGSize size = CGDisplayBounds(dspl).size;
        boolean_t main = CGDisplayIsMain(dspl);
        printf(" - id=<%d> main=<%d> size=<%f,%f>\n", dspl, main, size.width, size.height);
        CFArrayRef modes = CGDisplayCopyAllDisplayModes(dspl, NULL);

        for (int j = 0; j < CFArrayGetCount(modes); j++) {
            CGDisplayModeRef mode = (CGDisplayModeRef) CFArrayGetValueAtIndex(modes, j);
            printf("   - mode=<%p> size=<%lu,%lu> rate=<%f>\n",
                   mode,
                   CGDisplayModeGetWidth(mode),
                   CGDisplayModeGetHeight(mode),
                   CGDisplayModeGetRefreshRate(mode));
        }
    }
}
