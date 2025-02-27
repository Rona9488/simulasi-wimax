////
//// Copyright (C) 2006 Andras Varga
//// Based on the Mobility Framework's SnrEval by Marc Loebbers
////
//// This program is free software; you can redistribute it and/or
//// modify it under the terms of the GNU General Public License
//// as published by the Free Software Foundation; either version 2
//// of the License, or (at your option) any later version.
////
//// This program is distributed in the hope that it will be useful,
//// but WITHOUT ANY WARRANTY; without even the implied warranty of
//// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//// GNU General Public License for more details.
////
//// You should have received a copy of the GNU General Public License
//// along with this program; if not, see <http://www.gnu.org/licenses/>.
////
//
//#ifndef MODULATION_H
//#define MODULATION_H
//
//#include "IModulation.h"
//
///**
// * Ideal modulation which returns zero bit error rate, regardless of the parameters.
// */
//class INET_API NullModulation : public IModulation
//{
//  public:
//    virtual const char *getName() {return "no bit errors";}
//    virtual double calculateBER(double snir, double bandwidth, double bitrate);
//};
//
///**
// * BPSK modulation.
// */
//class INET_API BPSKModulation : public IModulation
//{
//  public:
//    virtual const char *getName() {return "BPSK";}
//    virtual double calculateBER(double snir, double bandwidth, double bitrate);
//};
//
///**
// * 16-QAM modulation.
// */
//class INET_API QAM16Modulation : public IModulation
//{
//  public:
//    virtual const char *getName() {return "16-QAM";}
//    virtual double calculateBER(double snir, double bandwidth, double bitrate);
//};
//
///**
// * 256-QAM modulation.
// */
//class INET_API QAM256Modulation : public IModulation
//{
//  public:
//    virtual const char *getName() {return "256-QAM";}
//    virtual double calculateBER(double snir, double bandwidth, double bitrate);
//};
//
//
//#endif
//
