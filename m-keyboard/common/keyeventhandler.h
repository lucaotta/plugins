/*
 * This file is part of meego-keyboard 
 *
 * Copyright (C) 2010-2011 Nokia Corporation and/or its subsidiary(-ies). All rights reserved.
 *
 * Contact: Mohammad Anwari <Mohammad.Anwari@nokia.com>
 *
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list 
 * of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list 
 * of conditions and the following disclaimer in the documentation and/or other materials 
 * provided with the distribution.
 * Neither the name of Nokia Corporation nor the names of its contributors may be 
 * used to endorse or promote products derived from this software without specific 
 * prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY 
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL 
 * THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */


#ifndef KEYEVENTHANDLER_H
#define KEYEVENTHANDLER_H

#include <QObject>
#include <QKeyEvent>
#include <QPoint>

struct KeyContext;
class MImAbstractKeyArea;
class KeyEvent;
class MImAbstractKey;
class QString;

/*!
 * \class KeyEventHandler
 * \brief Logic class to convert signals generated by buttons from
 * raw information into KeyEvent. Also filters clicks from shift button.
 */
class KeyEventHandler : public QObject
{
    Q_OBJECT

public:
    //! Constructs new instance of KeyEventHandler with given \a parent
    explicit KeyEventHandler(QObject *parent = 0);

    //! Connects this object to signals from given \a source
    void addEventSource(MImAbstractKeyArea *eventSource);

signals:
    /*!
     * \brief Emitted when key is pressed
     *
     * Note that this happens also when user keeps finger down/mouse
     * button pressed and moves over another key (event is about the new key)
     * \param event key event
     */
    void keyPressed(const KeyEvent &event);

    /*!
     * \brief Emitted when key is released
     *
     * Note that this happens also when user keeps finger down/mouse
     * button pressed and moves over another key (event is about the old key)
     * \param event key event
     */
    void keyReleased(const KeyEvent &event);

    /*!
     * \brief Emitted when user releases mouse button/lifts finger
     *
     * Except when done on a dead key
     * \param event key event
     */
    void keyClicked(const KeyEvent &event);

    /*!
     * \brief Emitted when key is long pressed.
     *
     * \param event key event
     */
    void longKeyPressed(const KeyEvent &event);

    /*!
     * \brief Emitted when shift key is pressed or released
     * \param state Contains true is key is pressed
     */
    void shiftPressed(bool state);

private slots:
    /*!
     * \brief Generates KeyEvent for given \a key and emits keyPressed
     */
    void handleKeyPress(const MImAbstractKey *key, const KeyContext &context);

    /*!
     * \brief Generates KeyEvent for given \a key and emits keyReleased
     */
    void handleKeyRelease(const MImAbstractKey *key, const KeyContext &context);

    /*!
     * \brief Generates KeyEvent for given \a key and emits keyClicked
     */
    void handleKeyClick(const MImAbstractKey *key, const KeyContext &context);

    /*!
     * \brief Generates KeyEvent for given \a key and emits longKeyPress
     */
    void handleLongKeyPress(const MImAbstractKey *key, const KeyContext &context);

private:
    //! Turn key button into a KeyEvent, considering event type and context of the invoked key.
    KeyEvent keyToKeyEvent(const MImAbstractKey &key,
                           QKeyEvent::Type eventType,
                           const KeyContext &keyContext) const;

private:
    //! Keeps track of shift up/down status.
    bool shiftHeldDown;

    //! When this is set true the next shift click is ignored.
    bool ignoreShiftClick;

#ifdef UNIT_TEST
    friend class Ut_KeyEventHandler;
#endif
};

#endif

