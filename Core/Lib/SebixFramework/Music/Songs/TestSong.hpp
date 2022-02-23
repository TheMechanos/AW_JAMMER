/*
 * TestSong.hpp
 *
 *  Created on: 27.01.2021
 *      Author: SHON
 */

#ifndef MUSIC_SONGS_TESTSONG_HPP_
#define MUSIC_SONGS_TESTSONG_HPP_

#include <Music/notesAndSong.hpp>

static const Tone ToneStarWars[] {
			{NOTE::AS4, 8}, {NOTE::AS4, 8}, {NOTE::AS4, 8}, {NOTE::F5, 2},
		    {NOTE::C6, 2},  {NOTE::AS5, 8}, {NOTE::A5, 8},  {NOTE::G5, 8},
		    {NOTE::F6, 2},  {NOTE::C6, 4},  {NOTE::AS5, 8}, {NOTE::A5, 8},
		    {NOTE::G5, 8},  {NOTE::F6, 2},  {NOTE::C6, 4},  {NOTE::AS5, 8},
		    {NOTE::A5, 8},  {NOTE::AS5, 8}, {NOTE::G5, 2},  {NOTE::C5, 8},
		    {NOTE::C5, 8},  {NOTE::C5, 8},  {NOTE::F5, 2},  {NOTE::C6, 2},
		    {NOTE::AS5, 8}, {NOTE::A5, 8},  {NOTE::G5, 8},  {NOTE::F6, 2},
		    {NOTE::C6, 4},  {NOTE::AS5, 8}, {NOTE::A5, 8},  {NOTE::G5, 8},
		    {NOTE::F6, 2},  {NOTE::C6, 4},  {NOTE::AS5, 8}, {NOTE::A5, 8},
		    {NOTE::AS5, 8}, {NOTE::G5, 2},  {NOTE::C5, -8}, {NOTE::C5, 16},
		    {NOTE::D5, -4}, {NOTE::D5, 8},  {NOTE::AS5, 8}, {NOTE::A5, 8},
		    {NOTE::G5, 8},  {NOTE::F5, 8},  {NOTE::F5, 8},  {NOTE::G5, 8},
		    {NOTE::A5, 8},  {NOTE::G5, 4},  {NOTE::D5, 8},  {NOTE::E5, 4},
		    {NOTE::C5, -8}, {NOTE::C5, 16}, {NOTE::D5, -4}, {NOTE::D5, 8},
		    {NOTE::AS5, 8}, {NOTE::A5, 8},  {NOTE::G5, 8},  {NOTE::F5, 8},
		    {NOTE::C6, -8}, {NOTE::G5, 16}, {NOTE::G5, 2},  {NOTE::REST, 8},
		    {NOTE::C5, 8},  {NOTE::D5, -4}, {NOTE::D5, 8},  {NOTE::AS5, 8},
		    {NOTE::A5, 8},  {NOTE::G5, 8},  {NOTE::F5, 8},  {NOTE::F5, 8},
		    {NOTE::G5, 8},  {NOTE::A5, 8},  {NOTE::G5, 4},  {NOTE::D5, 8},
		    {NOTE::E5, 4},  {NOTE::C6, -8}, {NOTE::C6, 16}, {NOTE::F6, 4},
		    {NOTE::DS6, 8}, {NOTE::CS6, 4}, {NOTE::C6, 8},  {NOTE::AS5, 4},
		    {NOTE::GS5, 8}, {NOTE::G5, 4},  {NOTE::F5, 8},  {NOTE::C6, 1}};
static Song songStarWars = Song(ToneStarWars, sizeof(ToneStarWars), 1600);

static const Tone ToneMario[] {
			{NOTE::E5, 8},   {NOTE::E5, 8},   {NOTE::REST, 8}, {NOTE::E5, 8},
		    {NOTE::REST, 8}, {NOTE::C5, 8},   {NOTE::E5, 8},   {NOTE::G5, 4},
		    {NOTE::REST, 4}, {NOTE::G4, 8},   {NOTE::REST, 4}, {NOTE::C5, -4},
		    {NOTE::G4, 8},   {NOTE::REST, 4}, {NOTE::E4, -4},  {NOTE::A4, 4},
		    {NOTE::B4, 4},   {NOTE::AS4, 8},  {NOTE::A4, 4},   {NOTE::G4, -8},
		    {NOTE::E5, -8},  {NOTE::G5, -8},  {NOTE::A5, 4},   {NOTE::F5, 8},
		    {NOTE::G5, 8},   {NOTE::REST, 8}, {NOTE::E5, 4},   {NOTE::C5, 8},
		    {NOTE::D5, 8},   {NOTE::B4, -4},  {NOTE::C5, -4},  {NOTE::G4, 8},
		    {NOTE::REST, 4}, {NOTE::E4, -4},  {NOTE::A4, 4},   {NOTE::B4, 4},
		    {NOTE::AS4, 8},  {NOTE::A4, 4},   {NOTE::G4, -8},  {NOTE::E5, -8},
		    {NOTE::G5, -8},  {NOTE::A5, 4},   {NOTE::F5, 8},   {NOTE::G5, 8},
		    {NOTE::REST, 8}, {NOTE::E5, 4},   {NOTE::C5, 8},   {NOTE::D5, 8},
		    {NOTE::B4, -4},  {NOTE::REST, 4}, {NOTE::G5, 8},   {NOTE::FS5, 8},
		    {NOTE::F5, 8},   {NOTE::DS5, 4},  {NOTE::E5, 8},   {NOTE::REST, 8},
		    {NOTE::GS4, 8},  {NOTE::A4, 8},   {NOTE::C4, 8},   {NOTE::REST, 8},
		    {NOTE::A4, 8},   {NOTE::C5, 8},   {NOTE::D5, 8},   {NOTE::REST, 4},
		    {NOTE::DS5, 4},  {NOTE::REST, 8}, {NOTE::D5, -4},  {NOTE::C5, 2},
		    {NOTE::REST, 2}, {NOTE::REST, 4}, {NOTE::G5, 8},   {NOTE::FS5, 8},
		    {NOTE::F5, 8},   {NOTE::DS5, 4},  {NOTE::E5, 8},   {NOTE::REST, 8},
		    {NOTE::GS4, 8},  {NOTE::A4, 8},   {NOTE::C4, 8},   {NOTE::REST, 8},
		    {NOTE::A4, 8},   {NOTE::C5, 8},   {NOTE::D5, 8},   {NOTE::REST, 4},
		    {NOTE::DS5, 4},  {NOTE::REST, 8}, {NOTE::D5, -4},  {NOTE::C5, 2},
		    {NOTE::REST, 2}, {NOTE::C5, 8},   {NOTE::C5, 4},   {NOTE::C5, 8},
		    {NOTE::REST, 8}, {NOTE::C5, 8},   {NOTE::D5, 4},   {NOTE::E5, 8},
		    {NOTE::C5, 4},   {NOTE::A4, 8},   {NOTE::G4, 2},   {NOTE::C5, 8},
		    {NOTE::C5, 4},   {NOTE::C5, 8},   {NOTE::REST, 8}, {NOTE::C5, 8},
		    {NOTE::D5, 8},   {NOTE::E5, 8},   {NOTE::REST, 1}, {NOTE::C5, 8},
		    {NOTE::C5, 4},   {NOTE::C5, 8},   {NOTE::REST, 8}, {NOTE::C5, 8},
		    {NOTE::D5, 4},   {NOTE::E5, 8},   {NOTE::C5, 4},   {NOTE::A4, 8},
		    {NOTE::G4, 2},   {NOTE::E5, 8},   {NOTE::E5, 8},   {NOTE::REST, 8},
		    {NOTE::E5, 8},   {NOTE::REST, 8}, {NOTE::C5, 8},   {NOTE::E5, 4},
		    {NOTE::G5, 4},   {NOTE::REST, 4}, {NOTE::G4, 4},   {NOTE::REST, 4},
		    {NOTE::C5, -4},  {NOTE::G4, 8},   {NOTE::REST, 4}, {NOTE::E4, -4},
		    {NOTE::A4, 4},   {NOTE::B4, 4},   {NOTE::AS4, 8},  {NOTE::A4, 4},
		    {NOTE::G4, -8},  {NOTE::E5, -8},  {NOTE::G5, -8},  {NOTE::A5, 4},
		    {NOTE::F5, 8},   {NOTE::G5, 8},   {NOTE::REST, 8}, {NOTE::E5, 4},
		    {NOTE::C5, 8},   {NOTE::D5, 8},   {NOTE::B4, -4},  {NOTE::C5, -4},
		    {NOTE::G4, 8},   {NOTE::REST, 4}, {NOTE::E4, -4},  {NOTE::A4, 4},
		    {NOTE::B4, 4},   {NOTE::AS4, 8},  {NOTE::A4, 4},   {NOTE::G4, -8},
		    {NOTE::E5, -8},  {NOTE::G5, -8},  {NOTE::A5, 4},   {NOTE::F5, 8},
		    {NOTE::G5, 8},   {NOTE::REST, 8}, {NOTE::E5, 4},   {NOTE::C5, 8},
		    {NOTE::D5, 8},   {NOTE::B4, -4},  {NOTE::E5, 8},   {NOTE::C5, 4},
		    {NOTE::G4, 8},   {NOTE::REST, 4}, {NOTE::GS4, 4},  {NOTE::A4, 8},
		    {NOTE::F5, 4},   {NOTE::F5, 8},   {NOTE::A4, 2},   {NOTE::D5, -8},
		    {NOTE::A5, -8},  {NOTE::A5, -8},  {NOTE::A5, -8},  {NOTE::G5, -8},
		    {NOTE::F5, -8},  {NOTE::E5, 8},   {NOTE::C5, 4},   {NOTE::A4, 8},
		    {NOTE::G4, 2},   {NOTE::E5, 8},   {NOTE::C5, 4},   {NOTE::G4, 8},
		    {NOTE::REST, 4}, {NOTE::GS4, 4},  {NOTE::A4, 8},   {NOTE::F5, 4},
		    {NOTE::F5, 8},   {NOTE::A4, 2},   {NOTE::B4, 8},   {NOTE::F5, 4},
		    {NOTE::F5, 8},   {NOTE::F5, -8},  {NOTE::E5, -8},  {NOTE::D5, -8},
		    {NOTE::C5, 8},   {NOTE::E4, 4},   {NOTE::E4, 8},   {NOTE::C4, 2},
		    {NOTE::E5, 8},   {NOTE::C5, 4},   {NOTE::G4, 8},   {NOTE::REST, 4},
		    {NOTE::GS4, 4},  {NOTE::A4, 8},   {NOTE::F5, 4},   {NOTE::F5, 8},
		    {NOTE::A4, 2},   {NOTE::D5, -8},  {NOTE::A5, -8},  {NOTE::A5, -8},
		    {NOTE::A5, -8},  {NOTE::G5, -8},  {NOTE::F5, -8},  {NOTE::E5, 8},
		    {NOTE::C5, 4},   {NOTE::A4, 8},   {NOTE::G4, 2},   {NOTE::E5, 8},
		    {NOTE::C5, 4},   {NOTE::G4, 8},   {NOTE::REST, 4}, {NOTE::GS4, 4},
		    {NOTE::A4, 8},   {NOTE::F5, 4},   {NOTE::F5, 8},   {NOTE::A4, 2},
		    {NOTE::B4, 8},   {NOTE::F5, 4},   {NOTE::F5, 8},   {NOTE::F5, -8},
		    {NOTE::E5, -8},  {NOTE::D5, -8},  {NOTE::C5, 8},   {NOTE::E4, 4},
		    {NOTE::E4, 8},   {NOTE::C4, 2},   {NOTE::C5, 8},   {NOTE::C5, 4},
		    {NOTE::C5, 8},   {NOTE::REST, 8}, {NOTE::C5, 8},   {NOTE::D5, 8},
		    {NOTE::E5, 8},   {NOTE::REST, 1}, {NOTE::C5, 8},   {NOTE::C5, 4},
		    {NOTE::C5, 8},   {NOTE::REST, 8}, {NOTE::C5, 8},   {NOTE::D5, 4},
		    {NOTE::E5, 8},   {NOTE::C5, 4},   {NOTE::A4, 8},   {NOTE::G4, 2},
		    {NOTE::E5, 8},   {NOTE::E5, 8},   {NOTE::REST, 8}, {NOTE::E5, 8},
		    {NOTE::REST, 8}, {NOTE::C5, 8},   {NOTE::E5, 4},   {NOTE::G5, 4},
		    {NOTE::REST, 4}, {NOTE::G4, 4},   {NOTE::REST, 4}, {NOTE::E5, 8},
		    {NOTE::C5, 4},   {NOTE::G4, 8},   {NOTE::REST, 4}, {NOTE::GS4, 4},
		    {NOTE::A4, 8},   {NOTE::F5, 4},   {NOTE::F5, 8},   {NOTE::A4, 2},
		    {NOTE::D5, -8},  {NOTE::A5, -8},  {NOTE::A5, -8},  {NOTE::A5, -8},
		    {NOTE::G5, -8},  {NOTE::F5, -8},  {NOTE::E5, 8},   {NOTE::C5, 4},
		    {NOTE::A4, 8},   {NOTE::G4, 2},   {NOTE::E5, 8},   {NOTE::C5, 4},
		    {NOTE::G4, 8},   {NOTE::REST, 4}, {NOTE::GS4, 4},  {NOTE::A4, 8},
		    {NOTE::F5, 4},   {NOTE::F5, 8},   {NOTE::A4, 2},   {NOTE::B4, 8},
		    {NOTE::F5, 4},   {NOTE::F5, 8},   {NOTE::F5, -8},  {NOTE::E5, -8},
		    {NOTE::D5, -8},  {NOTE::C5, 8},   {NOTE::E4, 4},   {NOTE::E4, 8},
		    {NOTE::C4, 2},   {NOTE::C5, -4},  {NOTE::G4, -4},  {NOTE::E4, 4},
		    {NOTE::A4, -8},  {NOTE::B4, -8},  {NOTE::A4, -8},  {NOTE::GS4, -8},
		    {NOTE::AS4, -8}, {NOTE::GS4, -8}, {NOTE::G4, 8},   {NOTE::D4, 8},
		    {NOTE::E4, -2}};
static Song songMario = Song(ToneMario, sizeof(ToneMario), 1200);


static const Tone TonePacman[]{
{NOTE::B4, 16},
{NOTE::B5, 16},
{NOTE::FS5, 16},
{NOTE::DS5, 16},
{NOTE::B5, 32},
{NOTE::FS5, -16},
{NOTE::DS5, 8},
{NOTE::C5, 16},
{NOTE::C6, 16},
{NOTE::G6, 16},
{NOTE::E6, 16},
{NOTE::C6, 32},
{NOTE::G6, -16},
{NOTE::E6, 8},
{NOTE::B4, 16},
{NOTE::B5, 16},
{NOTE::FS5, 16},
{NOTE::DS5, 16},
{NOTE::B5, 32},
{NOTE::FS5, -16},
{NOTE::DS5, 8},
{NOTE::DS5, 32},
{NOTE::E5, 32},
{NOTE::F5, 32},
{NOTE::F5, 32},
{NOTE::FS5, 32},
{NOTE::G5, 32},
{NOTE::G5, 32},
{NOTE::GS5, 32},
{NOTE::A5, 16},
{NOTE::B5, 8}};
static Song songPacman = Song(TonePacman, sizeof(TonePacman), 2000);


static const Tone ToneTetris[]{
    {NOTE::E5, 4},   {NOTE::B4, 8},   {NOTE::C5, 8},   {NOTE::D5, 4},
    {NOTE::C5, 8},   {NOTE::B4, 8},   {NOTE::A4, 4},   {NOTE::A4, 8},
    {NOTE::C5, 8},   {NOTE::E5, 4},   {NOTE::D5, 8},   {NOTE::C5, 8},
    {NOTE::B4, -4},  {NOTE::C5, 8},   {NOTE::D5, 4},   {NOTE::E5, 4},
    {NOTE::C5, 4},   {NOTE::A4, 4},   {NOTE::A4, 8},   {NOTE::A4, 4},
    {NOTE::B4, 8},   {NOTE::C5, 8},   {NOTE::D5, -4},  {NOTE::F5, 8},
    {NOTE::A5, 4},   {NOTE::G5, 8},   {NOTE::F5, 8},   {NOTE::E5, -4},
    {NOTE::C5, 8},   {NOTE::E5, 4},   {NOTE::D5, 8},   {NOTE::C5, 8},
    {NOTE::B4, 4},   {NOTE::B4, 8},   {NOTE::C5, 8},   {NOTE::D5, 4},
    {NOTE::E5, 4},   {NOTE::C5, 4},   {NOTE::A4, 4},   {NOTE::A4, 4},
    {NOTE::REST, 4}, {NOTE::E5, 4},   {NOTE::B4, 8},   {NOTE::C5, 8},
    {NOTE::D5, 4},   {NOTE::C5, 8},   {NOTE::B4, 8},   {NOTE::A4, 4},
    {NOTE::A4, 8},   {NOTE::C5, 8},   {NOTE::E5, 4},   {NOTE::D5, 8},
    {NOTE::C5, 8},   {NOTE::B4, -4},  {NOTE::C5, 8},   {NOTE::D5, 4},
    {NOTE::E5, 4},   {NOTE::C5, 4},   {NOTE::A4, 4},   {NOTE::A4, 8},
    {NOTE::A4, 4},   {NOTE::B4, 8},   {NOTE::C5, 8},   {NOTE::D5, -4},
    {NOTE::F5, 8},   {NOTE::A5, 4},   {NOTE::G5, 8},   {NOTE::F5, 8},
    {NOTE::E5, -4},  {NOTE::C5, 8},   {NOTE::E5, 4},   {NOTE::D5, 8},
    {NOTE::C5, 8},   {NOTE::B4, 4},   {NOTE::B4, 8},   {NOTE::C5, 8},
    {NOTE::D5, 4},   {NOTE::E5, 4},   {NOTE::C5, 4},   {NOTE::A4, 4},
    {NOTE::A4, 4},   {NOTE::REST, 4}, {NOTE::E5, 2},   {NOTE::C5, 2},
    {NOTE::D5, 2},   {NOTE::B4, 2},   {NOTE::C5, 2},   {NOTE::A4, 2},
    {NOTE::GS4, 2},  {NOTE::B4, 4},   {NOTE::REST, 8}, {NOTE::E5, 2},
    {NOTE::C5, 2},   {NOTE::D5, 2},   {NOTE::B4, 2},   {NOTE::C5, 4},
    {NOTE::E5, 4},   {NOTE::A5, 2},   {NOTE::GS5, 2}};
static Song songTetris = Song(ToneTetris, sizeof(ToneTetris), 1600);



static const Tone ToneHP[]{
    {NOTE::REST, 2}, {NOTE::D4, 4},   {NOTE::G4, -4},  {NOTE::AS4, 8},
    {NOTE::A4, 4},   {NOTE::G4, 2},   {NOTE::D5, 4},   {NOTE::C5, -2},
    {NOTE::A4, -2},  {NOTE::G4, -4},  {NOTE::AS4, 8},  {NOTE::A4, 4},
    {NOTE::F4, 2},   {NOTE::GS4, 4},  {NOTE::D4, -1},  {NOTE::D4, 4},
    {NOTE::G4, -4},  {NOTE::AS4, 8},  {NOTE::A4, 4},   {NOTE::G4, 2},
    {NOTE::D5, 4},   {NOTE::F5, 2},   {NOTE::E5, 4},   {NOTE::DS5, 2},
    {NOTE::B4, 4},   {NOTE::DS5, -4}, {NOTE::D5, 8},   {NOTE::CS5, 4},
    {NOTE::CS4, 2},  {NOTE::B4, 4},   {NOTE::G4, -1},  {NOTE::AS4, 4},
    {NOTE::D5, 2},   {NOTE::AS4, 4},  {NOTE::D5, 2},   {NOTE::AS4, 4},
    {NOTE::DS5, 2},  {NOTE::D5, 4},   {NOTE::CS5, 2},  {NOTE::A4, 4},
    {NOTE::AS4, -4}, {NOTE::D5, 8},   {NOTE::CS5, 4},  {NOTE::CS4, 2},
    {NOTE::D4, 4},   {NOTE::D5, -1},  {NOTE::REST, 4}, {NOTE::AS4, 4},
    {NOTE::D5, 2},   {NOTE::AS4, 4},  {NOTE::D5, 2},   {NOTE::AS4, 4},
    {NOTE::F5, 2},   {NOTE::E5, 4},   {NOTE::DS5, 2},  {NOTE::B4, 4},
    {NOTE::DS5, -4}, {NOTE::D5, 8},   {NOTE::CS5, 4},  {NOTE::CS4, 2},
    {NOTE::AS4, 4},  {NOTE::G4, -1}};
static Song songHP = Song(ToneHP, sizeof(ToneHP), 1600);


static const Tone ToneKeyboardCat[]{
    {NOTE::REST, 1}, {NOTE::REST, 1}, {NOTE::C4, 4}, {NOTE::E4, 4},
    {NOTE::G4, 4},   {NOTE::E4, 4},   {NOTE::C4, 4}, {NOTE::E4, 8},
    {NOTE::G4, -4},  {NOTE::E4, 4},   {NOTE::A3, 4}, {NOTE::C4, 4},
    {NOTE::E4, 4},   {NOTE::C4, 4},   {NOTE::A3, 4}, {NOTE::C4, 8},
    {NOTE::E4, -4},  {NOTE::C4, 4},   {NOTE::G3, 4}, {NOTE::B3, 4},
    {NOTE::D4, 4},   {NOTE::B3, 4},   {NOTE::G3, 4}, {NOTE::B3, 8},
    {NOTE::D4, -4},  {NOTE::B3, 4},   {NOTE::G3, 4}, {NOTE::G3, 8},
    {NOTE::G3, -4},  {NOTE::G3, 8},   {NOTE::G3, 4}, {NOTE::G3, 4},
    {NOTE::G3, 4},   {NOTE::G3, 8},   {NOTE::G3, 4}, {NOTE::C4, 4},
    {NOTE::E4, 4},   {NOTE::G4, 4},   {NOTE::E4, 4}, {NOTE::C4, 4},
    {NOTE::E4, 8},   {NOTE::G4, -4},  {NOTE::E4, 4}, {NOTE::A3, 4},
    {NOTE::C4, 4},   {NOTE::E4, 4},   {NOTE::C4, 4}, {NOTE::A3, 4},
    {NOTE::C4, 8},   {NOTE::E4, -4},  {NOTE::C4, 4}, {NOTE::G3, 4},
    {NOTE::B3, 4},   {NOTE::D4, 4},   {NOTE::B3, 4}, {NOTE::G3, 4},
    {NOTE::B3, 8},   {NOTE::D4, -4},  {NOTE::B3, 4}, {NOTE::G3, -1}};
static Song songKeyboardCat = Song(ToneKeyboardCat, sizeof(ToneKeyboardCat), 1500);

static const Tone ToneBethoven[]{
    {NOTE::E4, 4}, {NOTE::E4, 4}, {NOTE::F4, 4},  {NOTE::G4, 4}, {NOTE::G4, 4},
    {NOTE::F4, 4}, {NOTE::E4, 4}, {NOTE::D4, 4},  {NOTE::C4, 4}, {NOTE::C4, 4},
    {NOTE::D4, 4}, {NOTE::E4, 4}, {NOTE::E4, -4}, {NOTE::D4, 8}, {NOTE::D4, 2},
    {NOTE::E4, 4}, {NOTE::E4, 4}, {NOTE::F4, 4},  {NOTE::G4, 4}, {NOTE::G4, 4},
    {NOTE::F4, 4}, {NOTE::E4, 4}, {NOTE::D4, 4},  {NOTE::C4, 4}, {NOTE::C4, 4},
    {NOTE::D4, 4}, {NOTE::E4, 4}, {NOTE::D4, -4}, {NOTE::C4, 8}, {NOTE::C4, 2},
    {NOTE::D4, 4}, {NOTE::D4, 4}, {NOTE::E4, 4},  {NOTE::C4, 4}, {NOTE::D4, 4},
    {NOTE::E4, 8}, {NOTE::F4, 8}, {NOTE::E4, 4},  {NOTE::C4, 4}, {NOTE::D4, 4},
    {NOTE::E4, 8}, {NOTE::F4, 8}, {NOTE::E4, 4},  {NOTE::D4, 4}, {NOTE::C4, 4},
    {NOTE::D4, 4}, {NOTE::G3, 2}, {NOTE::E4, 4},  {NOTE::E4, 4}, {NOTE::F4, 4},
    {NOTE::G4, 4}, {NOTE::G4, 4}, {NOTE::F4, 4},  {NOTE::E4, 4}, {NOTE::D4, 4},
    {NOTE::C4, 4}, {NOTE::C4, 4}, {NOTE::D4, 4},  {NOTE::E4, 4}, {NOTE::D4, -4},
    {NOTE::C4, 8}, {NOTE::C4, 2}};
static Song songBethoven = Song(ToneBethoven, sizeof(ToneBethoven), 2100);

static const Tone ToneCannonInd[]{
    {NOTE::FS4, 2}, {NOTE::E4, 2},  {NOTE::D4, 2},  {NOTE::CS4, 2},
    {NOTE::B3, 2},  {NOTE::A3, 2},  {NOTE::B3, 2},  {NOTE::CS4, 2},
    {NOTE::FS4, 2}, {NOTE::E4, 2},  {NOTE::D4, 2},  {NOTE::CS4, 2},
    {NOTE::B3, 2},  {NOTE::A3, 2},  {NOTE::B3, 2},  {NOTE::CS4, 2},
    {NOTE::D4, 2},  {NOTE::CS4, 2}, {NOTE::B3, 2},  {NOTE::A3, 2},
    {NOTE::G3, 2},  {NOTE::FS3, 2}, {NOTE::G3, 2},  {NOTE::A3, 2},
    {NOTE::D4, 4},  {NOTE::FS4, 8}, {NOTE::G4, 8},  {NOTE::A4, 4},
    {NOTE::FS4, 8}, {NOTE::G4, 8},  {NOTE::A4, 4},  {NOTE::B3, 8},
    {NOTE::CS4, 8}, {NOTE::D4, 8},  {NOTE::E4, 8},  {NOTE::FS4, 8},
    {NOTE::G4, 8},  {NOTE::FS4, 4}, {NOTE::D4, 8},  {NOTE::E4, 8},
    {NOTE::FS4, 4}, {NOTE::FS3, 8}, {NOTE::G3, 8},  {NOTE::A3, 8},
    {NOTE::G3, 8},  {NOTE::FS3, 8}, {NOTE::G3, 8},  {NOTE::A3, 2},
    {NOTE::G3, 4},  {NOTE::B3, 8},  {NOTE::A3, 8},  {NOTE::G3, 4},
    {NOTE::FS3, 8}, {NOTE::E3, 8},  {NOTE::FS3, 4}, {NOTE::D3, 8},
    {NOTE::E3, 8},  {NOTE::FS3, 8}, {NOTE::G3, 8},  {NOTE::A3, 8},
    {NOTE::B3, 8},  {NOTE::G3, 4},  {NOTE::B3, 8},  {NOTE::A3, 8},
    {NOTE::B3, 4},  {NOTE::CS4, 8}, {NOTE::D4, 8},  {NOTE::A3, 8},
    {NOTE::B3, 8},  {NOTE::CS4, 8}, {NOTE::D4, 8},  {NOTE::E4, 8},
    {NOTE::FS4, 8}, {NOTE::G4, 8},  {NOTE::A4, 2},  {NOTE::A4, 4},
    {NOTE::FS4, 8}, {NOTE::G4, 8},  {NOTE::A4, 4},  {NOTE::FS4, 8},
    {NOTE::G4, 8},  {NOTE::A4, 8},  {NOTE::A3, 8},  {NOTE::B3, 8},
    {NOTE::CS4, 8}, {NOTE::D4, 8},  {NOTE::E4, 8},  {NOTE::FS4, 8},
    {NOTE::G4, 8},  {NOTE::FS4, 4}, {NOTE::D4, 8},  {NOTE::E4, 8},
    {NOTE::FS4, 8}, {NOTE::CS4, 8}, {NOTE::A3, 8},  {NOTE::A3, 8},
    {NOTE::CS4, 4}, {NOTE::B3, 4},  {NOTE::D4, 8},  {NOTE::CS4, 8},
    {NOTE::B3, 4},  {NOTE::A3, 8},  {NOTE::G3, 8},  {NOTE::A3, 4},
    {NOTE::D3, 8},  {NOTE::E3, 8},  {NOTE::FS3, 8}, {NOTE::G3, 8},
    {NOTE::A3, 8},  {NOTE::B3, 4},  {NOTE::G3, 4},  {NOTE::B3, 8},
    {NOTE::A3, 8},  {NOTE::B3, 4},  {NOTE::CS4, 8}, {NOTE::D4, 8},
    {NOTE::A3, 8},  {NOTE::B3, 8},  {NOTE::CS4, 8}, {NOTE::D4, 8},
    {NOTE::E4, 8},  {NOTE::FS4, 8}, {NOTE::G4, 8},  {NOTE::A4, 2}};
static Song songCannonInd = Song(ToneCannonInd, sizeof(ToneCannonInd), 2400);


static const Tone ToneStarTrek[]{
	{NOTE::D4, -8},
	{NOTE::G4, 16},
	{NOTE::C5, -4},
	{NOTE::B4, 8},
	{NOTE::G4, -16},
	{NOTE::E4, -16},
	{NOTE::A4, -16},
	{NOTE::D5, 2}
};
static Song songStarTrek = Song(ToneStarTrek, sizeof(ToneStarTrek), 2400);




#endif /* MUSIC_SONGS_TESTSONG_HPP_ */
