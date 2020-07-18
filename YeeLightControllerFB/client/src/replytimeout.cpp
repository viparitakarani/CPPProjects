#include "../header/replytimeout.h"


ReplyTimeout::ReplyTimeout(QNetworkReply* reply, const int timeout) : QObject(reply) {
  Q_ASSERT(reply);
  if (reply && reply->isRunning())
     m_timer.start(timeout, this);
}

void ReplyTimeout::set(QNetworkReply* reply, const int timeout) {
  new ReplyTimeout(reply, timeout);
}

void ReplyTimeout::timerEvent(QTimerEvent * ev) {
  if (!m_timer.isActive() || ev->timerId() != m_timer.timerId())
     return;
  auto reply = static_cast<QNetworkReply*>(parent());
  if (reply->isRunning())
  {
    reply->close();
    qDebug() << "Request Timeout!!";
  }
  m_timer.stop();
}
