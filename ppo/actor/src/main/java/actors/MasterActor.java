package actors;

import akka.actor.Props;
import akka.actor.ReceiveTimeout;
import akka.actor.UntypedActor;
import akka.event.Logging;
import akka.event.LoggingAdapter;
import scala.concurrent.duration.Duration;
import searchers.SearchSiteInfo;

import java.util.List;
import java.util.concurrent.CompletableFuture;

public class MasterActor extends UntypedActor
{
    LoggingAdapter log = Logging.getLogger(getContext().system(), this);

    private final List<SearchSiteInfo> info;
    private final MasterActorResult result;
    private final CompletableFuture<MasterActorResult> futureResult;

    public MasterActor(List<SearchSiteInfo> info, Duration duration, CompletableFuture<MasterActorResult> futureResult) {
        this.info = info;
        this.futureResult = futureResult;

        this.getContext().setReceiveTimeout(duration);
        result = new MasterActorResult();
    }

    @Override
    public void onReceive(Object o) throws Throwable {
        if (o instanceof String) {
            sendRequest((String) o);
        } else if (o instanceof ChildActorResultMessage) {
            ChildActorResultMessage childResult = (ChildActorResultMessage) o;
            log.info("Receive response from {}", childResult.info.desc);

            result.result.put(childResult.info.desc,
                              childResult.response);

            if (result.result.size() == info.size())
                returnResult();
        } else if (o instanceof ReceiveTimeout) {
            log.info("Request timeout");
            returnResult();
        }
    }

    private void sendRequest(String request) {
        log.info("Send request '{}' to searchers", request);

        if (!context().children().isEmpty()) {
            log.error("Call for actor for the second time");
            return;
        }
        info.forEach(searcher ->
                getContext()
                        .actorOf(Props.create(ChildActor.class, searcher))
                        .tell(request, getSelf()));
    }

    private void returnResult() {
        futureResult.complete(result);
        getContext().system().stop(getSelf());
    }
}