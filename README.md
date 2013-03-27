# Learning DSP

Some very basic and crude implementation of DSP functions to test my understanding of signal processing.

Currently includes:

 * A Discrete Fourier Transform (DFT) function
 * Hanning Window when performing the DFT
 * Spectral magnitude calculation

And some useful tidbits to play with it:

 * Wave file loader
 * ASCII representation of a spectrum

# Usage


First parameter is a wave file, and the second parameter is the number of samples to perform a DFT on (the DFT will have that same length).

Wave file must be 16 bits, 1 channel only. I have tested mostly at 11025kHz although other bitrates should work too.


    $ ./fftfun samples/sine-3200.wav 512
    ./fftfun: put some DSP classes to work
    ChunkId   : RIFF
    Format    : WAVE

    Audio Format: 1
    Num Channels: 1
    Sample Rate: 11025
    Byte Rate: 22050
    Block Align: 2
    BitsPerSample: 16

    Data size: 44100
    NumSamples: 22050
    File duration: 2.000000
    Power @     0 Hz: -134.98 dB Magnitude: 0.00000
    Power @    22 Hz: -126.56 dB Magnitude: 0.00000
    ...
    Power @  2993 Hz:  -71.25 dB Magnitude: 0.00027 #############################
    Power @  3015 Hz:  -68.37 dB Magnitude: 0.00038 ################################
    Power @  3036 Hz:  -65.11 dB Magnitude: 0.00056 ###################################
    Power @  3058 Hz:  -61.40 dB Magnitude: 0.00085 #######################################
    Power @  3079 Hz:  -57.03 dB Magnitude: 0.00141 ###########################################
    Power @  3101 Hz:  -51.78 dB Magnitude: 0.00258 #################################################
    Power @  3122 Hz:  -45.13 dB Magnitude: 0.00554 #######################################################
    Power @  3144 Hz:  -35.98 dB Magnitude: 0.01588 #################################################################
    Power @  3165 Hz:  -20.51 dB Magnitude: 0.09428 ################################################################################
    Power @  3187 Hz:   -4.06 dB Magnitude: 0.62672 ################################################################################################
    Power @  3208 Hz:   -2.81 dB Magnitude: 0.72369 ##################################################################################################
    Power @  3230 Hz:  -14.71 dB Magnitude: 0.18384 ######################################################################################
    Power @  3252 Hz:  -33.45 dB Magnitude: 0.02126 ###################################################################
    Power @  3273 Hz:  -43.43 dB Magnitude: 0.00674 #########################################################
    Power @  3295 Hz:  -50.49 dB Magnitude: 0.00299 ##################################################
    Power @  3316 Hz:  -56.00 dB Magnitude: 0.00159 #############################################
    Power @  3338 Hz:  -60.51 dB Magnitude: 0.00094 ######...


# Author

Thomas Sarlandie - @sarfata - github.com/sarfata

# License

Public domain code. Do whatever you want with it. Comes with no warranty, etc.
