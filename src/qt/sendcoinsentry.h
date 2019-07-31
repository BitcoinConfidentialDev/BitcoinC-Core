// Copyright (c) 2011-2018 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_SENDCOINSENTRY_H
#define BITCOIN_QT_SENDCOINSENTRY_H

#include <qt/walletmodel.h>

#include <QStackedWidget>

class WalletModel;
class PlatformStyle;

namespace Ui {
    class SendCoinsEntry;
}

/**
 * A single entry in the dialog for sending bitcoins.
 * Stacked widget, with different UIs for payment requests
 * with a strong payee identity.
 */
class SendCoinsEntry : public QStackedWidget
{
    Q_OBJECT

public:
    explicit SendCoinsEntry(const PlatformStyle *platformStyle, QWidget *parent = 0, bool fSpending = true, bool coldstake = false, bool fConvert = false);
    ~SendCoinsEntry();

    void setModel(WalletModel *model);
    bool validate(interfaces::Node& node);
    SendCoinsRecipient getValue();

    /** Return whether the entry is still empty and unedited */
    bool isClear();

    void setValue(const SendCoinsRecipient &value);
    void setAddress(const QString &address);
    void setNarration(const QString &sNarr);
    void setAmount(const CAmount &amount);

    void setStakeAddress(const QString &address);

    /** Set up the tab chain manually, as Qt messes up the tab chain by default in some cases
     *  (issue https://bugreports.qt-project.org/browse/QTBUG-10907).
     */
    QWidget *setupTabChain(QWidget *prev);

    void setFocus();
    void hideDeleteButton();
    void hideMessage();
    void hideAddLabel();

public Q_SLOTS:
    void clear();
    void checkSubtractFeeFromAmount();

Q_SIGNALS:
    void removeEntry(SendCoinsEntry *entry);
    void useAvailableBalance(SendCoinsEntry* entry);
    void payAmountChanged();
    void subtractFeeFromAmountChanged();

private Q_SLOTS:
    void deleteClicked();
    void useAvailableBalanceClicked();
    void on_payTo_textChanged(const QString &address);
    void on_addressBookButton_clicked();
    void on_addressBookButton_convert_clicked();
    void on_pasteButton_clicked();
    void on_pasteButton_convert_clicked();
    void updateDisplayUnit();

    void on_pasteButton_cs_clicked();
    void on_addressBookButton_cs_clicked();

    void on_pasteButton2_cs_clicked();
    void on_addressBookButton2_cs_clicked();

private:
    SendCoinsRecipient recipient;
    Ui::SendCoinsEntry *ui;
    WalletModel *model;
    const PlatformStyle *platformStyle;

    bool updateLabel(const QString &address);
public:
    bool fSpending;
    bool fConvert;
    bool fColdstake;
};

#endif // BITCOIN_QT_SENDCOINSENTRY_H
